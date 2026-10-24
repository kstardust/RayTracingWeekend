#ifndef _CAMERA_H
#define _CAMERA_H

#include "hittable.h"
#include "vec3.h"
#include <atomic>
#include <vector>

class camera {
public:
  double aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  int samples_per_pixel = 10;
  int max_trace_depth = 50;
  double fov = 20;
  point3 lookfrom = point3(0, 0, 0);
  point3 lookat = point3(0, 0, -1);
  vec3 vup = vec3(0, 1, 0);

  double defocus_angle = 0;
  double focus_dist = 10;

  void render(const hittable &world, unsigned int concurrency);

private:
  int image_height;
  point3 center;
  vec3 pixel_delta_u;
  vec3 pixel_delta_v;
  point3 pixel00_loc;
  double pixel_samples_scale;
  vec3 back, up, right; // normally i would call it 'front', but in this
                        // tutorial it points opposite the view direction
  std::atomic<int> progress;
  std::vector<vec3> data;

  vec3 defocus_disk_v;
  vec3 defocus_disk_u;

  void initialize();

  color ray_color(const ray &r, int depth, const hittable &world) const;
  void process_pixels(const hittable &world, size_t start, size_t end);

  ray get_ray(int i, int j) const;
  vec3 sample_square() const;
  point3 defocus_sample() const;
};

#endif
