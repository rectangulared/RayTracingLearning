#pragma once

#include <iostream>

#include "vec3.hpp"
#include "interval.hpp"

void writeColor(std::ostream& out, color pixelColor, int samplesPerPixel) 
{
    auto r = pixelColor.r();
    auto g = pixelColor.g();
    auto b = pixelColor.b();

    // Divide the color by the number of samples and gamma-correct for gamma = 2.0
    auto scale = 1.0 / samplesPerPixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    static const interval intensity(0.000, 0.999);
    out << static_cast<int>(256 * intensity.clamp(r)) << ' '
        << static_cast<int>(256 * intensity.clamp(g)) << ' '
        << static_cast<int>(256 * intensity.clamp(b)) << '\n';
}
