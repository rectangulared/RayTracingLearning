#pragma once

#include "vec3.hpp"

class ray 
{

public:
    point3 origin;
    vec3<double> direction;
    
    ray() {}
    ray(const point3& _origin, const vec3<double>& _direction) : origin(_origin), direction(_direction) {}

    point3 getOrigin() const { return origin; }
    point3 at(double t) const { return origin + t * direction; }
    vec3<double> getDirection() const { return direction; }

};