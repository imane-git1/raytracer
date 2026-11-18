#pragma once

#include "math/vector.h"
#include "geometry/ray.h"

class Camera
{
public:
    Camera(const Vector &position, double screenWidth);

    const Vector &position() const;
    Ray rayThroughCentre() const;
    Ray rayThroughPixel(int column, int row, int imageWidth, int imageHeight) const;

private:
    Vector _position;
    double _screenWidth;
};