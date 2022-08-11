#include <iostream>

#include "utils.hpp"

#include "camera.hpp"
#include "color.hpp"
#include "hittableList.hpp"
#include "material.hpp"
#include "scene.hpp"
#include "sphere.hpp"

void random_spheres(scene& randScene) {
    randScene.imageWidth = 1200;
    randScene.aspectRatio = 16.0 / 9.0;
    randScene.samplesPerPixel = 100;

    randScene.cam.vFOV = 20;
    randScene.cam.focusDist = 10.0;
    randScene.cam.aperture = 0.1;
    randScene.cam._origin = vec3(-13.0, 2.0, 3.0);
    randScene.cam._lookAt = vec3(0.0, 0.0, 0.0);
    randScene.cam._vUp = vec3(0.0, 1.0, 0.0);

    hittableList& world = randScene.world;

    auto groundMaterial = std::make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(std::make_shared<sphere>(point3(0.0, -1000, 0.0), 1000.0, groundMaterial));

    for (int a = -11; a < 11; a++) 
    {
        for (int b = -11; b < 11; b++) 
        {
            auto chooseMat = randomDouble();
            point3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

            if ((center - point3(4.0, 0.2, 0.0)).length() > 0.9) 
            {
                std::shared_ptr<material> sphereMaterial;

                if (chooseMat < 0.8) 
                {
                    // diffuse
                    auto albedo = vec3::random() * vec3::random();
                    sphereMaterial = std::make_shared<lambertian>(albedo);
                    world.add(std::make_shared<sphere>(center, 0.2, sphereMaterial));
                }
                else if (chooseMat < 0.95) 
                {
                    // metal
                    auto albedo = vec3::random(0.5, 1);
                    auto fuzz = randomDouble(0.0, 0.5);
                    sphereMaterial = std::make_shared<metal>(albedo, fuzz);
                    world.add(std::make_shared<sphere>(center, 0.2, sphereMaterial));
                }
                else 
                {
                    // glass
                    sphereMaterial = std::make_shared<dielectric>(1.5);
                    world.add(std::make_shared<sphere>(center, 0.2, sphereMaterial));
                }
            }
        }
    }

    auto material1 = std::make_shared<dielectric>(1.5);
    world.add(std::make_shared<sphere>(point3(0.0, 1, 0.0), 1.0, material1));

    auto material2 = std::make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(std::make_shared<sphere>(point3(-4.0, 1.0, 0.0), 1.0, material2));

    auto material3 = std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<sphere>(point3(4.0, 1.0, 0.0), 1.0, material3));
}


int main() {
    scene scene_desc;
    random_spheres(scene_desc);
    scene_desc.render();
}