#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "hittable.h"

class material {
public:
  virtual ~material() = default;

  virtual bool scatter(const ray &r, const hit_record &rec, color &attenuation,
                       ray &scatterd) {
    return false;
  };
};

class lambertian : public material {
public:
  lambertian(const color &albedo) : albedo(albedo) {}

  bool scatter(const ray &r, const hit_record &rec, color &attenuation,
               ray &scattered) {
    vec3 lambert_reflect = rec.norm + random_unit_vector();
    if (lambert_reflect.near_zero()) {
      lambert_reflect = rec.norm;
    }
    scattered = ray(rec.p, lambert_reflect);
    attenuation = albedo;
    return true;
  }

private:
  color albedo;
};

class metal : public material {
public:
  metal(const color &albedo, double fuzz)
      : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}
  bool scatter(const ray &r, const hit_record &rec, color &attenuation,
               ray &scattered) {
    vec3 rf = reflect(r.direction(), rec.norm);
    rf = unit_vector(rf) + (fuzz * random_unit_vector());
    scattered = ray(rec.p, rf);
    attenuation = albedo;
    return dot(scattered.direction(), rec.norm) > 0;
  }

private:
  vec3 albedo;
  double fuzz;
};

class dielectric : public material {
public:
  dielectric(double refraction_index) : refraction_index(refraction_index) {}
  bool scatter(const ray &r, const hit_record &rec, color &attenuation,
               ray &scattered) {
    attenuation = color(1.0, 1.0, 1.0);
    double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;
    vec3 unit_direction = unit_vector(r.direction());

    double cos_theta = std::fmin(1.0, dot(-unit_direction, rec.norm));
    double sin_theta = std::sqrt(1 - cos_theta * cos_theta);
    vec3 dir;
    if (ri * sin_theta > 1.0 || reflectance(cos_theta, ri) > random_double()) {
      // snell's law does not have solution in this case
      dir = reflect(unit_direction, rec.norm);
    } else {
      dir = refract(unit_direction, rec.norm, ri);
    }

    scattered = ray(rec.p, dir);
    return true;
  }

private:
  double refraction_index;

  static double reflectance(double cosine, double refraction_index) {
    // schlick's approximation for reflectance.
    auto r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow((1 - cosine), 5);
  }
};

#endif
