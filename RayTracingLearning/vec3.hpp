#pragma once

#include <cmath>
#include <iostream>

class vec3 {
public:
    double vArr[3];
    vec3() : vArr{ 0 ,0 ,0 } {}
    vec3(double _x, double _y, double _z) : vArr{ _x, _y, _z } {}

    double x() const { return vArr[0]; }
    double y() const { return vArr[1]; }
    double z() const { return vArr[2]; }
    double r() const { return vArr[0]; }
    double g() const { return vArr[1]; }
    double b() const { return vArr[2]; }

    double operator[](int i) const { return vArr[i]; }
    double& operator[](int i) { return vArr[i]; }

    vec3 operator-() const { return vec3(-vArr[0], -vArr[1], -vArr[2]); }

    vec3& operator+=(const vec3& v) 
    {
        vArr[0] += v.vArr[0];
        vArr[1] += v.vArr[1];
        vArr[2] += v.vArr[2];
        return *this;
    }

    vec3& operator*=(const double t) 
    {
        vArr[0] *= t;
        vArr[1] *= t;
        vArr[2] *= t;
        return *this;
    }

    vec3& operator/=(const double t) 
    {
        return *this *= 1 / t;
    }

    double length() const 
    {
        return sqrt(squaredLength());
    }

    double squaredLength() const 
    {
        return vArr[0] * vArr[0] + vArr[1] * vArr[1] + vArr[2] * vArr[2];
    }

    //Check if we close to zero
    bool nearZero() const 
    {
        const auto s = 1e-8;
        return (fabs(vArr[0]) < s) && (fabs(vArr[1]) < s) && (fabs(vArr[2]) < s);
    }

    static vec3 random() 
    {
        return vec3(randomDouble(), randomDouble(), randomDouble());
    }

    static vec3 random(double min, double max) 
    {
        return vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
    }
};

//With this class we can also represent 3D point and color
using point3 = vec3;
using color = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) 
{
    return out << v.vArr[0] << ' ' << v.vArr[1] << ' ' << v.vArr[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) 
{
    return vec3(u.vArr[0] + v.vArr[0], u.vArr[1] + v.vArr[1], u.vArr[2] + v.vArr[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) 
{
    return vec3(u.vArr[0] - v.vArr[0], u.vArr[1] - v.vArr[1], u.vArr[2] - v.vArr[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) 
{
    return vec3(u.vArr[0] * v.vArr[0], u.vArr[1] * v.vArr[1], u.vArr[2] * v.vArr[2]);
}

inline vec3 operator*(double t, const vec3& v) 
{
    return vec3(t * v.vArr[0], t * v.vArr[1], t * v.vArr[2]);
}

inline vec3 operator*(const vec3& v, double t) 
{
    return t * v;
}

inline vec3 operator/(vec3 v, double t) 
{
    return (1.0 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) 
{
    return u.vArr[0] * v.vArr[0]
        + u.vArr[1] * v.vArr[1]
        + u.vArr[2] * v.vArr[2];
}

inline vec3 cross(const vec3& u, const vec3& v) 
{
    return vec3(
        u.vArr[1] * v.vArr[2] - u.vArr[2] * v.vArr[1],
        u.vArr[2] * v.vArr[0] - u.vArr[0] * v.vArr[2],
        u.vArr[0] * v.vArr[1] - u.vArr[1] * v.vArr[0]
    );
}

inline vec3 unitVector(vec3 v) 
{
    return v / v.length();
}

inline vec3 randomInUnitDisk() 
{
    while (true) 
    {
        auto tmp = vec3(randomDouble(-1.0, 1.0), randomDouble(-1.0, 1.0), 0.0);
        if (tmp.squaredLength() >= 1.0) continue;
        return tmp;
    }
}

inline vec3 randomInUnitSphere() 
{
    while (true) 
    {
        auto tmp = vec3::random(-1.0, 1.0);
        if (tmp.squaredLength() >= 1.0) continue;
        return tmp;
    }
}

inline vec3 randomUnitVector() { return unitVector(randomInUnitSphere()); }

inline vec3 randomInHemisphere(const vec3& normal) 
{
    vec3 inUnitSphere = randomInUnitSphere();
    return dot(inUnitSphere, normal) > 0.0 ? inUnitSphere : -inUnitSphere;
}

inline vec3 reflect(const vec3& v, const vec3& n) 
{
    return v - 2.0 * dot(v, n) * n;
}

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) 
{
    auto cosTheta = fmin(dot(-uv, n), 1.0);
    vec3 rOutPerp = etai_over_etat * (uv + cosTheta * n);
    vec3 rOutParallel = -sqrt(fabs(1.0 - rOutPerp.squaredLength())) * n;
    return rOutPerp + rOutParallel;
}