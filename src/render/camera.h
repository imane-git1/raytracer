#pragma once

#include "math/vector.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "image/image.h"
#include "scene/scene.h"

class Camera
{
public:
    Camera(const Vector &position, double screenWidth);

    [[nodiscard]] const Vector &position() const;
    
    [[nodiscard]] Ray rayThroughPixel(int column, int row, int imageWidth, int imageHeight) const;

    [[nodiscard]] Image render(const Scene &scene, int width, int height) const;

private:
    Vector _position;
    double _screenWidth;
};