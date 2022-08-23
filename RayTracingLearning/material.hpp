#pragma once

#include "utils.hpp"

class hitRecord;

class material 
{
public:
    virtual ~material() = default;

    virtual bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered) const = 0;
};


class lambertian : public material 
{
public:
    color albedo;
    lambertian(const color& _albedo) : albedo(_albedo) {}

    bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered) const override
    {
        auto scatterDirection = rec.normal + randomUnitVector<double>();

        // Catch degenerate scatter direction
        if (scatterDirection.nearZero()) scatterDirection = rec.normal;

        scattered = ray(rec.p, scatterDirection);
        attenuation = albedo;
        return true;
    }
};


class metal : public material 
{
public:
    double fuzz;
    color albedo;

    metal(const color& _albedo, double _fuzz) : albedo(_albedo), fuzz(_fuzz < 1.0 ? _fuzz : 1.0) {}

    bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered) const override
    {
        vec3<double> reflected = reflect<double>(unitVector<double>(rIn.getDirection()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz * randomInUnitSphere<double>());
        attenuation = albedo;
        return (dot<double>(scattered.getDirection(), rec.normal) > 0.0);
    }
};


class dielectric : public material 
{
public:
    double refractionIndex;

    dielectric(double _refractionIndex) : refractionIndex(_refractionIndex) {}

    bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered) const override 
    {
        attenuation = color(1.0, 1.0, 1.0);
        double refractionRatio = rec.frontFace ? (1.0 / refractionIndex) : refractionIndex;

        vec3<double> unitDirection = unitVector<double>(rIn.getDirection());
        double cosTheta = fmin(dot(-unitDirection, rec.normal), 1.0);
        double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

        bool cannotRefract = refractionRatio * sinTheta > 1.0;
        vec3<double> direction;

        if (cannotRefract || reflectance(cosTheta, refractionRatio) > randomNumber<double>())
            direction = reflect(unitDirection, rec.normal);
        else
            direction = refract(unitDirection, rec.normal, refractionRatio);

        scattered = ray(rec.p, direction);
        return true;
    }

private:
    static double reflectance(double cosine, double rIndex)
    {
        //Schlick's approximation for reflectance.
        auto r0 = (1.0 - rIndex) / (1.0 + rIndex);
        r0 *= r0;
        return r0 + (1.0 - r0) * pow((1.0 - cosine), 5);
    }
};

