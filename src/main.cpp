#include "colour/colour.h"
#include "geometry/plane.h"
#include "geometry/sphere.h"
#include "image/image.h"
#include "io/png_saver.h"
#include "math/vector.h"
#include "material/material.h"
#include "render/camera.h"
#include "scene/scene.h"

#include <memory>

int main()
{
    Camera camera(Vector(0, 0, -1), 2.0);
    Scene scene(Vector(-1, 1, -1));
    scene.add(std::make_unique<Sphere>(
        Vector(0, 0, 9), 5.0, Material(Colour(1, 0, 0))));
    scene.add(std::make_unique<Plane>(
        Vector(0, -5, 0), Vector(0, 1, 0), Material(Colour(0.8, 0.8, 0.8))));

    Image image = camera.render(scene, 400, 300);

    PngSaver saver;
    saver.save(image, "image.png");
    return 0;
}