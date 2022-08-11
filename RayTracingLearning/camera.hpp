#pragma once

#include "utils.hpp"

class camera 
{
public:
    double vFOV = 4.0;
    double aperture = 0.0;
    double focusDist = 10.0;

    point3 _origin = point3(0.0, 0.0, -1.0);
    point3 _lookAt = point3(0.0, 0.0, 0.0);
    vec3   _vUp = vec3(0.0, 1.0, 0.0);

    void initialize(double aspectRatio = 1.0) 
    {
        auto theta = degreesToRadians(vFOV);
        auto h = tan(theta / 2.0);
        auto viewportHeight = 2.0 * h;
        auto viewportWidth = aspectRatio * viewportHeight;

        w = unitVector(_origin - _lookAt);
        u = unitVector(cross(_vUp, w));
        v = cross(w, u);

        origin = _origin;
        horizontal = focusDist * viewportWidth * u;
        vertical = focusDist * viewportHeight * v;
        lowerLeftCorner = origin - horizontal / 2.0 - vertical / 2.0 - focusDist * w;

        lensRadius = aperture / 2.0;
    }

    ray getRay(double s, double t) const 
    {
        vec3 rd = lensRadius * randomInUnitDisk();
        vec3 offset = u * rd.x() + v * rd.y();

        return ray(origin + offset, lowerLeftCorner + s * horizontal + t * vertical - origin - offset);
    }

private:
    double lensRadius;
    point3 origin;
    point3 lowerLeftCorner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
};