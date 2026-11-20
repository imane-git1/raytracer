#pragma once

#include "math/vector.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "image/image.h"

class Camera
{
public:
    Camera(const Vector &position, double screenWidth);

    const Vector &position() const;
    
    Ray rayThroughPixel(int column, int row, int imageWidth, int imageHeight) const;

    Image render(const Sphere &sphere, int width, int height) const;

private:
    Vector _position;
    double _screenWidth;
};