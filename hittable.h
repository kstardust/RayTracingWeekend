#ifndef _HITTABLE_H
#define  _HITTABLE_H

#include "vec3.h"
#include "ray.h"

struct hit_record {
    point3 p;
    vec3 norm;
    double t;
};

class hittable {
 public:
    virtual ~hittable() = default;
    virtual bool hit(const ray &r, double ray_t_min, double ray_t_max, hit_record &rec) const = 0;
};

#endif

