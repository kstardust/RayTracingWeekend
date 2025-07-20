#include "hittable_list.h"

bool hittable_list::hit(const ray &r, const interval &ray_range,
                        hit_record &rec) const {
  hit_record tmp;
  bool any_hit = false;
  double nearest = ray_range.max;

  for (const auto &obj : objects) {
    if (obj->hit(r, interval(ray_range.min, nearest), tmp)) {
      nearest = tmp.t;
      rec = tmp;
      any_hit = true;
    }
  }

  return any_hit;
}
