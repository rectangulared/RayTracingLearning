#pragma once

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degreesToRadians(double degrees) { return degrees * pi / 180.0; }

//Random valuse from 0.0 to 1.0
inline double randomDouble() { return rand() / (RAND_MAX + 1.0); }

inline double randomDouble(double min, double max) { return min + (max - min) * randomDouble(); }

inline int randomInt(int min, int max) { return static_cast<int>(randomDouble(min, max + 1.0)); }

// Common Headers

#include "interval.hpp"
#include "ray.hpp"
#include "vec3.hpp"