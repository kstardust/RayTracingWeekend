#ifndef _SPHERE_H
#define _SPHERE_H

#include "hittable.h"

class sphere : public hittable {
public:
  virtual bool hit(const ray &r, const interval &ray_range,
                   hit_record &rec) const override;
  sphere(const point3 &origin, double radius)
      : origin(origin), radius(radius) {};

private:
  point3 origin;
  double radius;
};

#endif
