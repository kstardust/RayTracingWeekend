#ifndef _HITTABLE_H
#define _HITTABLE_H

#include "common.h"
#include "ray.h"

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
  virtual bool hit(const ray &r, const interval &ray_range,
                   hit_record &rec) const = 0;
};

#endif
