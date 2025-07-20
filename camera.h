#ifndef _CAMERA_H
#define _CAMERA_H

#include "hittable.h"

class camera {
public:
  double aspect_ratio = 16.0 / 9.0;
  int image_width = 800;
  int samples_per_pixel = 10;

  void render(const hittable &world);

private:
  int image_height;
  point3 center;
  vec3 pixel_delta_u;
  vec3 pixel_delta_v;
  point3 pixel00_loc;
  double pixel_samples_scale;

  void initialize();

  color ray_color(const ray &r, const hittable &world) const;

  ray get_ray(int i, int j) const;
  vec3 sample_square() const;
};

#endif
