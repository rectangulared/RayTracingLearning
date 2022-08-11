#pragma once

#include "utils.hpp"

#include "camera.hpp"
#include "hittableList.hpp"

#include <iostream>


class scene {

public:
    camera cam;
    hittableList world;

    int    imageWidth = 1200;
    int    samplesPerPixel = 100;
    int    maxDepth = 20;
    double aspectRatio = 1.0;

    void render() 
    {
        const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

        cam.initialize(aspectRatio);

        std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

        for (int i = imageHeight - 1; i >= 0 ; --i)
        {
            std::clog << "\rLines remaining: " << i << ' ' << std::flush;
            for (int j = 0; j < imageWidth; ++j)
            {
                color pixelColor(0.0, 0.0, 0.0);
                for (int sample = 0; sample < samplesPerPixel; ++sample) 
                {
                    auto u = (j + randomDouble()) / (imageWidth - 1);
                    auto v = (i + randomDouble()) / (imageHeight - 1);
                    ray r = cam.getRay(u, v);
                    pixelColor += rayColor(r, maxDepth);
                }
                writeColor(std::cout, pixelColor, samplesPerPixel);
            }
        }
        std::clog << "\nDone.\n";
    }

private:

    color rayColor(const ray& r, int depth) {
        hitRecord rec;

        if (depth <= 0) return color(0.0, 0.0, 0.0);

        if (world.hit(r, interval(0.001, infinity), rec)) 
        {
            ray scattered;
            color attenuation;
            if (rec.mat->scatter(r, rec, attenuation, scattered))
                return attenuation * rayColor(scattered, depth - 1);
            return color(0.0, 0.0, 0.0);
        }

        vec3 unitDirection = unitVector(r.getDirection());
        auto t = 0.5 * (unitDirection.y() + 1.0);
        return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
    }
};