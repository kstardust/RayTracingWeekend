#ifndef _CAMERA_H
#define _CAMERA_H

#include "hittable.h"

class camera {
public:
  double aspect_ratio = 16.0 / 9.0;
  int image_width = 800;

  void render(const hittable &world);

private:
  int image_height;
  point3 center;
  vec3 pixel_delta_u;
  vec3 pixel_delta_v;
  point3 pixel00_loc;

  void initialize();

  color ray_color(const ray &r, const hittable &world) const;
};

#endif
