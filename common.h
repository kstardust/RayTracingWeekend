#ifndef _COMMON_H
#define _COMMON_H

#include <cmath>
#include <cstdio>
#include <iostream>
#include <limits>
#include <memory>

#define PROGRESS_FINISHED "###################"
#define PROGRESS_REMAIN "                   "
#define PROGRESS_BAR_SIZE 20

// C++ Std Usings

using std::make_shared;
using std::shared_ptr;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

// Common Headers

#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif
