#include "sphere.h"

bool sphere::hit(const ray &r, const interval &ray_range,
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

  // try the nearest one
  double root = (-b - sqr) / (2 * a);

  if (!ray_range.surrounds(root)) {
    root = (-b + sqr) / (2 * a);
    if (!ray_range.surrounds(root))
      return false;
  }

  rec.t = root;
  rec.p = r.at(root);
  rec.norm = (rec.p - origin) / radius;
  rec.mat = mat;

  return true;
}
