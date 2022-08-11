#pragma once

#include "utils.hpp"

class material;

class hitRecord 
{
public:
    bool frontFace;
    double t;

    std::shared_ptr<material> mat;

    point3 p;
    vec3 normal;

    void setFaceNormal(const ray& r, const vec3& outwardNormal) 
    {
        frontFace = dot(r.getDirection(), outwardNormal) < 0.0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class hittable
{
public:
    virtual ~hittable() = default;

    virtual bool hit(const ray& r, interval rayT, hitRecord& rec) const = 0;
};

