#pragma once

#include "hittable.hpp"

class sphere : public hittable {

public:
    double radius;
    std::shared_ptr<material> mat;
    point3 center;

    sphere(point3 _center, double _radius, std::shared_ptr<material> _mat) : center(_center), radius(_radius), mat(_mat) {};

    bool hit(const ray& r, interval rayT, hitRecord& rec) const override 
    {
        vec3 oc = r.getOrigin() - center;
        auto a = r.getDirection().squaredLength();
        auto halfB = dot(oc, r.getDirection());
        auto c = oc.squaredLength() - radius * radius;

        auto discriminant = halfB * halfB - a * c;
        if (discriminant < 0.0) return false;

        auto sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (-halfB - sqrtd) / a;
        if (!rayT.contains(root)) 
        {
            root = (-halfB + sqrtd) / a;
            if (!rayT.contains(root)) return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outwardNormal = (rec.p - center) / radius;
        rec.setFaceNormal(r, outwardNormal);
        rec.mat = mat;

        return true;
    }
};