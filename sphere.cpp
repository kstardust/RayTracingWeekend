#include "sphere.h"

bool sphere::hit(const ray &r, double ray_t_min, double ray_t_max,
                 hit_record &rec) const {
  vec3 dir = r.direction();
  point3 orig = r.origin();
  vec3 oc = orig - origin;

  double a = dot(dir, dir);
  double b = 2 * dot(dir, oc);
  double c = dot(oc, oc) - radius * radius;

  double sq = b * b - 4 * a * c;

  // root only exists when b^2 - 4ac >= 0
  if (sq < 0)
    return false;

  double sqr = std::sqrt(sq);

  // return the nearest one
  double root1 = (-b - sqr) / (2 * a);
  double root2 = (-b + sqr) / (2 * a);

  double near = root1, far = root2;

  if (abs(root1) > abs(root2)) {
    near = root2;
    far = root1;
  }

  double root = near;

  if (root > ray_t_max && root < ray_t_min) {
    root = far;
    if (root > ray_t_max && root < ray_t_min)
      return false;
  }

  rec.t = root;
  rec.p = r.at(root);
  rec.norm = (rec.p - origin) / radius;

  return true;
}
