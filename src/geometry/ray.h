#pragma once

#include "math/vector.h"

class Ray
{
public:
    Ray(const Vector &origin, const Vector &direction);

    [[nodiscard]] const Vector &origin() const;
    [[nodiscard]] const Vector &direction() const;
    [[nodiscard]] Vector at(double t) const;

private:
    Vector _origin;
    Vector _direction;
};