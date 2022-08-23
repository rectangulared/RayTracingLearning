#pragma once

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// Constants

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

// Utility Functions
template<typename T>
T degreesToRadians(T degrees) { return degrees * pi / 180.0; }

//Random valuse from 0.0 to 1.0
template<typename T>
T randomNumber() { return rand() / (RAND_MAX + 1.0); }

template<typename T>
T randomNumber(T min, T max) { return min + (max - min) * randomNumber<T>(); }

// Common Headers

#include "interval.hpp"
#include "ray.hpp"
#include "vec3.hpp"