#include <iostream>

#include "render/camera.h"
#include "colour/colour.h"
#include "math/vector.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "render/trace.h"

int main()
{
    Camera camera(Vector(0, 0, -1), 2.0);
    Sphere sphere(Vector(0, 0, 9), 5.0, Colour(1, 0, 0));

    Ray ray = camera.rayThroughCentre();

    Colour black(0, 0, 0);
    Colour pixel = trace(ray, sphere);

    std::cout << "(" << pixel.r() << ", " << pixel.g() << ", " << pixel.b() << ")\n";
    return 0;
}