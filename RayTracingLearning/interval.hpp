#pragma once

#include "utils.hpp"

class interval
{
public:
    double min, max;

    static const interval empty, universe;

    interval() : min(+infinity), max(-infinity) {}

    interval(double _min, double _max) : min(_min), max(_max) {}

    interval(const interval& a, const interval& b) : min(fmin(a.min, b.min)), max(fmax(a.max, b.max)) {}

    bool contains(double x) const
    {
        return min <= x && x <= max;
    }

    double size() const
    {
        return max - min;
    }

    double clamp(double x) const
    {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    interval expand(double delta) const
    {
        const auto padding = delta / 2.0;
        return interval(min - padding, max + padding);
    }
};

interval operator+(const interval& interval, double displacement);

interval operator+(double displacement, const interval& interval);
