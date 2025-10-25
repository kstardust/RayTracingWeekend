#ifndef _HITTABLE_H
#define _HITTABLE_H

#include "common.h"
#include "ray.h"

class material;

class hit_record {
public:
  point3 p;
  vec3 norm;
  double t;
  shared_ptr<material> mat;
  bool front_face;

  void set_face_normal(const ray &r, const vec3 &outward_normal) {
    front_face = dot(r.direction(), outward_normal) < 0;
    norm = front_face ? outward_normal : -outward_normal;
  }
};

class hittable {
public:
  virtual ~hittable() = default;
  virtual bool hit(const ray &r, const interval &ray_range,
                   hit_record &rec) const = 0;
};

#endif
