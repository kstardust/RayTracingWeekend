#ifndef _HITTABLE_LIST_H
#define _HITTABLE_LIST_H

#include <vector>

#include "common.h"
#include "hittable.h"

class hittable_list : public hittable {
public:
  std::vector<shared_ptr<hittable>> objects;

  hittable_list() {}
  hittable_list(shared_ptr<hittable> object) { add_object(object); };

  void clear() { objects.clear(); }

  void add_object(shared_ptr<hittable> object) { objects.push_back(object); }

  bool hit(const ray &r, const interval &ray_range,
           hit_record &rec) const override;
};

#endif
