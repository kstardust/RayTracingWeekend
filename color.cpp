#include "color.h"
#include "common.h"

/* gamma 2 */
double linear_to_gamma(double l) {
  if (l > 0)
    return std::sqrt(l);
  return 0;
}

void write_color(FILE *out, const color &pixel_color) {
  auto r = linear_to_gamma(pixel_color.x());
  auto g = linear_to_gamma(pixel_color.y());
  auto b = linear_to_gamma(pixel_color.z());

  const interval intensity(0.000, 0.999);
  int rbyte = int(256 * intensity.clamp(r));
  int gbyte = int(256 * intensity.clamp(g));
  int bbyte = int(256 * intensity.clamp(b));

  fprintf(out, "%d %d %d\n", rbyte, gbyte, bbyte);
}
