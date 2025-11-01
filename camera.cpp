#include "camera.h"
#include "common.h"
#include "material.h"

void camera::render(const hittable &world) {
  initialize();

  printf("P3\n%d %d\n255\n", image_width, image_height);

  for (int v = 0; v < image_height; v++) {
    int progress = int(double(v) / (image_height - 1) * PROGRESS_BAR_SIZE);
    fprintf(stderr, "\r[%.*s%.*s]", progress, PROGRESS_FINISHED,
            PROGRESS_BAR_SIZE - progress, PROGRESS_REMAIN);
    for (int u = 0; u < image_width; u++) {
      point3 pixel_center = pixel00_loc + v * pixel_delta_v + u * pixel_delta_u;
      point3 ray_dir = pixel_center - center;
      ray r(center, ray_dir);

      color pixel_color = color(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; s++) {
        ray r = get_ray(u, v);
        pixel_color += ray_color(r, max_trace_depth, world);
      }

      write_color(stdout, pixel_color * pixel_samples_scale);
    }
  }
  fprintf(stderr, "\r[%.*s] \n", PROGRESS_BAR_SIZE, PROGRESS_FINISHED);
}

ray camera::get_ray(int i, int j) const {
  vec3 offset = sample_square();
  auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) +
                      ((j + offset.y()) * pixel_delta_v);

  vec3 origin = defocus_angle <= 0 ? center : defocus_sample();
  return ray(origin, pixel_sample - origin);
}

vec3 camera::defocus_sample() const {
  auto p = random_in_unit_disk();
  return center + (p.x() * defocus_disk_u) + (p.y() * defocus_disk_v);
}

vec3 camera::sample_square() const {
  return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

void camera::initialize() {
  image_height = int(image_width / aspect_ratio);
  image_height = 1.0 > image_height ? 1.0 : image_height;

  pixel_samples_scale = 1.0 / samples_per_pixel;

  double h = std::tan(degrees_to_radians(fov / 2.0));
  double viewport_height = h * 2 * focus_dist;
  double viewport_width =
      viewport_height * (double(image_width) / image_height);
  center = lookfrom;

  back = unit_vector(lookfrom - lookat);
  right = unit_vector(cross(vup, back));
  up = cross(back, right);

  vec3 viewport_u = viewport_width * right;
  vec3 viewport_v = viewport_height * -up;

  pixel_delta_u = viewport_u / image_width;
  pixel_delta_v = viewport_v / image_height;

  vec3 viewport_upper_left =
      center - (focus_dist * back) - (viewport_u / 2 + viewport_v / 2);
  pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

  double defocus_radius =
      std::tan(degrees_to_radians(defocus_angle / 2)) * focus_dist;

  defocus_disk_u = right * defocus_radius;
  defocus_disk_v = up * defocus_radius;
}

color camera::ray_color(const ray &r, int depth, const hittable &world) const {
  if (depth <= 0)
    return vec3(0, 0, 0);

  hit_record rec;
  // ignore very closed hit because it might be ourselves because of float point
  // rounding error.
  if (world.hit(r, interval(0.001, infinity), rec)) {
    ray scatterd;
    color attenuation;
    if (rec.mat->scatter(r, rec, attenuation, scatterd)) {
      return attenuation * ray_color(scatterd, depth - 1, world);
    }
    // no scatter, swallows all light
    return color(0, 0, 0);
  }

  vec3 u_dir = unit_vector(r.direction());
  double a = 0.5 * (1 + u_dir.y());
  return (1 - a) * color(1, 1, 1) + a * color(0.5, 0.7, 1.0);
}
