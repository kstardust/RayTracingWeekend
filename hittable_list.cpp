#include "hittable_list.h"

bool hittable_list::hit(const ray &r, double ray_t_min, double ray_t_max,
                        hit_record &rec) const {
  hit_record tmp;
  bool any_hit = false;
  double nearest = ray_t_max;

  for (const auto &obj : objects) {
    if (obj->hit(r, ray_t_min, nearest, tmp)) {
      nearest = tmp.t;
      rec = tmp;
      any_hit = true;
    }
  }

  return any_hit;
}
