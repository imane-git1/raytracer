#include "colour/colour.h"
#include "geometry/sphere.h"
#include "image/image.h"
#include "io/png_saver.h"
#include "math/vector.h"
#include "render/camera.h"

int main()
{
    Camera camera(Vector(0, 0, -1), 2.0);
    Sphere sphere(Vector(0, 0, 9), 5.0, Colour(1, 0, 0));

    Image image = camera.render(sphere, 400, 300);

    PngSaver saver;
    saver.save(image, "image.png");
    return 0;
}