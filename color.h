#ifndef _COLOR_H
#define _COLOR_H

#include "vec3.h"

using color = vec3;

void write_color(FILE *out, const color &pixel_color);

#endif
