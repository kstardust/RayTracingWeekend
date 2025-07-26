#ifndef _SPHERE_H
#define _SPHERE_H

#include "hittable.h"

class sphere : public hittable {
public:
  virtual bool hit(const ray &r, const interval &ray_range,
                   hit_record &rec) const override;
  sphere(const point3 &origin, double radius, shared_ptr<material> mat)
      : origin(origin), radius(std::fmax(0, radius)), mat(mat) {};

private:
  point3 origin;
  double radius;
  shared_ptr<material> mat;
};

#endif
