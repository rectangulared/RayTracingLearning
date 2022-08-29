#pragma once

#include <cmath>

constexpr double NEAR_ZERO = 1e-8;

template<typename T> class vec3;
template<typename T> std::ostream& operator<<(std::ostream&, const vec3<T>&);
template<typename T> vec3<T> operator+(const vec3<T>&, const vec3<T>&);
template<typename T> vec3<T> operator-(const vec3<T>&, const vec3<T>&);
template<typename T> vec3<T> operator*(const vec3<T>&, const vec3<T>&);
template<typename T> vec3<T> operator*(const vec3<T>&, const T&);
template<typename T> vec3<T> operator*(const T&, const vec3<T>&);
template<typename T> vec3<T> operator/(const vec3<T>&, const T&);

template<typename T>
class vec3
{
public:
	vec3() : vArr{ 0, 0, 0 } {}
	vec3(T _x, T _y, T _z) : vArr{ _x, _y, _z } {};

	T x() const { return vArr[0]; }
	T y() const { return vArr[1]; }
	T z() const { return vArr[2]; }
	T r() const { return vArr[0]; }
	T g() const { return vArr[1]; }
	T b() const { return vArr[2]; }

	T operator[](int i) const { return vArr[i]; }
	T& operator[](int i) { return vArr[i]; }

	vec3<T>& operator+=(const vec3& v)
	{
		vArr[0] += v[0];
		vArr[1] += v[1];
		vArr[2] += v[2];
		return *this;
	}

	vec3<T>& operator-=(const vec3& v)
	{
		vArr[0] -= v[0];
		vArr[1] -= v[1];
		vArr[2] -= v[2];
		return *this;
	}

	vec3<T>& operator*=(const T& t)
	{
		vArr[0] *= t;
		vArr[1] *= t;
		vArr[2] *= t;
		return *this;
	}

	vec3<T>& operator/=(const T& t)
	{
		return *this *= 1.0 / t;
	}


	friend std::ostream& operator<<(std::ostream&, const vec3<T>&);
	friend vec3<T> operator+<>(const vec3<T>&, const vec3<T>&);
	friend vec3<T> operator-<>(const vec3<T>&, const vec3<T>&);
	friend vec3<T> operator*<>(const vec3<T>&, const vec3<T>&);
	friend vec3<T> operator*<>(const vec3<T>&, const T&);
	friend vec3<T> operator*<>(const T&, const vec3<T>&);
	friend vec3<T> operator/<>(const vec3<T>&, const T&);

	vec3<T> operator-() const { return vec3<T>(-vArr[0], -vArr[1], -vArr[2]); }

	T length() const
	{
		return sqrt(squaredLength());
	}

	T squaredLength() const
	{
		return vArr[0] * vArr[0] + vArr[1] * vArr[1] + vArr[2] * vArr[2];
	}

	bool nearZero() const
	{
		return (fabs(vArr[0]) < NEAR_ZERO & fabs(vArr[1]) < NEAR_ZERO & fabs(vArr[2]) < NEAR_ZERO);
	}

	static vec3<T> random()
	{
		return vec3<T>(randomNumber<T>(), randomNumber<T>(), randomNumber<T>());
	}

	static vec3<T> random(T min, T max)
	{
		return vec3<T>(randomNumber<T>(min, max), randomNumber<T>(min, max), randomNumber<T>(min, max));
	}

	template<typename T> friend vec3<T> cross(const vec3<T>& u, const vec3<T>& v);
	template<typename T> friend T dot(const vec3<T>& u, const vec3<T>& v);
	template<typename T> friend vec3<T> randomInUnitDisk();
	template<typename T> friend vec3<T> randomInUnitSphere();
	template<typename T> friend vec3<T> randomInHemisphere(const vec3<T>& normal);
	template<typename T> friend vec3<T> randomUnitVector();
	template<typename T> friend vec3<T> reflect(const vec3<T>& v, const vec3<T>& n);
	template<typename T> friend vec3<T> refract(const vec3<T>& uv, const vec3<T>& n, double etaiOverEtat);
	template<typename T> friend vec3<T> unitVector(vec3<T> v);

private:
	T vArr[3];
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const vec3<T>& v)
{
	return out << v.vArr[0] << ' ' << v.vArr[1] << ' ' << v.vArr[2];
}

template<typename T>
vec3<T> operator+(const vec3<T>& u, const vec3<T>& v)
{
	return vec3<T>(u.vArr[0] + v.vArr[0], u.vArr[1] + v.vArr[1], u.vArr[2] + v.vArr[2]);
}

template<typename T>
vec3<T> operator-(const vec3<T>& u, const vec3<T>& v)
{
	return vec3<T>(u.vArr[0] - v.vArr[0], u.vArr[1] - v.vArr[1], u.vArr[2] - v.vArr[2]);
}

template<typename T>
vec3<T> operator*(const vec3<T>& u, const vec3<T>& v)
{
	return vec3<T>(u.vArr[0] * v.vArr[0], u.vArr[1] * v.vArr[1], u.vArr[2] * v.vArr[2]);
}

template<typename T>
vec3<T> operator*(const vec3<T>& v, const T& t)
{
	return vec3<T>(v.vArr[0] * t, v.vArr[1] * t, v.vArr[2] * t);
}

template<typename T>
vec3<T> operator*(const T& t, const vec3<T>& v)
{
	return v * t;
}

template<typename T>
vec3<T> operator/(const vec3<T>& v, const T& t)
{
	return (1.0 / t) * v;
}

template<typename T>
vec3<T> cross(const vec3<T>& u, const vec3<T>& v)
{
	return vec3<T>(
		u.vArr[1] * v.vArr[2] - u.vArr[2] * v.vArr[1],
		u.vArr[2] * v.vArr[0] - u.vArr[0] * v.vArr[2],
		u.vArr[0] * v.vArr[1] - u.vArr[1] * v.vArr[0]
		);
}

template<typename T>
T dot(const vec3<T>& u, const vec3<T>& v)
{
	return u.vArr[0] * v.vArr[0] + u.vArr[1] * v.vArr[1] + u.vArr[2] * v.vArr[2];
}

template<typename T>
vec3<T> randomInUnitDisk()
{
	while (true)
	{
		auto temp = vec3<T>(randomNumber(-1.0, 1.0), randomNumber(-1.0, 1.0), 0.0);
		if (temp.squaredLength() >= 1.0) continue;
		return temp;
	}
}

template<typename T>
vec3<T> randomInUnitSphere()
{
	while (true)
	{
		vec3<T> temp = vec3<T>::random(-1.0, 1.0);
		if (temp.squaredLength() >= 1.0) continue;
		return temp;
	}
}

template<typename T>
vec3<T> randomInHemisphere(const vec3<T>& normal)
{
	vec3<T> inUnitSphere = randomInUnitSphere<T>();
	return dot(inUnitSphere, normal) > 0.0 ? inUnitSphere : -inUnitSphere;
}

template<typename T>
vec3<T> randomUnitVector() { return unitVector(randomInUnitSphere<T>()); }

template<typename T>
vec3<T> reflect(const vec3<T>& v, const vec3<T>& n)
{
	return v - 2.0 * dot(v, n) * n;
}

template<typename T>
vec3<T> refract(const vec3<T>& uv, const vec3<T>& n, double etaiOverEtat)
{
	auto cosTheta = fmin(dot(-uv, n), 1.0);
	vec3<T> rOutPerp = etaiOverEtat * (uv + cosTheta * n);
	vec3<T> rOutParallel = -sqrt(fabs(1.0 - rOutPerp.squaredLength())) * n;
	return rOutPerp + rOutParallel;
}

template<typename T>
vec3<T> unitVector(vec3<T> v)
{
	return v.length() > 0 ? (v / v.length()) : v;
}

using point3 = vec3<double>;
using color = vec3<double>;