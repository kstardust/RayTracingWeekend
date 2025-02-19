#include "hittable.h"

class sphere : public hittable {
 public:
    virtual bool hit(const ray &r, double ray_t_min, double ray_t_max, hit_record &rec) const override;
    sphere(const point3 &origin, double radius)
        : origin(origin), radius(radius) {};


  private:
    point3 origin;
    double radius;
};
