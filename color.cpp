#include "color.h"
#include "common.h"

void write_color(FILE *out, const color &pixel_color) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  int rbyte = 255.999 * r;
  int gbyte = 255.999 * g;
  int bbyte = 255.999 * b;

  fprintf(out, "%d %d %d\n", rbyte, gbyte, bbyte);
}
