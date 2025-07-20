#ifndef _HITTABLE_H
#define _HITTABLE_H

#include "ray.h"
#include "vec3.h"

class hit_record {
public:
  point3 p;
  vec3 norm;
  double t;
  bool front_face;

  void set_face_normal(const ray &r, const vec3 &outward_normal) {

    front_face = dot(r.direction(), outward_normal) < 0;
    norm = front_face ? norm : -norm;
  }
};
class hittable {
public:
  virtual ~hittable() = default;
  virtual bool hit(const ray &r, double ray_t_min, double ray_t_max,
                   hit_record &rec) const = 0;
};

#endif
