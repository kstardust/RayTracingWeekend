#ifndef _HITTABLE_H
#define _HITTABLE_H

#include "common.h"

class hit_record {
public:
  point3 p;
  vec3 norm;
  double t;
  bool front_face;
};

class hittable {
public:
  virtual ~hittable() = default;
  virtual bool hit(const ray &r, double ray_t_min, double ray_t_max,
                   hit_record &rec) const = 0;
};

#endif
