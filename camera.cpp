#include "camera.h"
#include "common.h"

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

  return ray(center, pixel_sample - center);
}

vec3 camera::sample_square() const {
  return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

void camera::initialize() {
  image_height = int(image_width / aspect_ratio);
  image_height = 1.0 > image_height ? 1.0 : image_height;

  pixel_samples_scale = 1.0 / samples_per_pixel;

  double focal_length = 1.0;
  double viewport_height = 2.0;
  double viewport_width =
      viewport_height * (double(image_width) / image_height);
  center = point3(0, 0, 0);

  vec3 viewport_u = vec3(viewport_width, 0, 0);
  vec3 viewport_v = vec3(0, -viewport_height, 0);

  pixel_delta_u = viewport_u / image_width;
  pixel_delta_v = viewport_v / image_height;

  vec3 viewport_upper_left =
      center - vec3(0, 0, focal_length) - (viewport_u / 2 + viewport_v / 2);
  pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

color camera::ray_color(const ray &r, int depth, const hittable &world) const {
  if (depth <= 0)
    return vec3(0, 0, 0);

  hit_record rec;
  // ignore very closed hit because it might be ourselves because of float point
  // rounding error.
  if (world.hit(r, interval(0.01, infinity), rec)) {
    vec3 lambert_reflect = rec.norm + random_unit_vector();
    return 0.5 * ray_color(ray(rec.p, lambert_reflect), depth - 1, world);
  }

  vec3 u_dir = unit_vector(r.direction());
  double a = 0.5 * (1 + u_dir.y());
  return (1 - a) * color(1, 1, 1) + a * color(0.5, 0.7, 1.0);
}
