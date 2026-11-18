#pragma once

#include "colour/colour.h"
#include "math/vector.h"
#include "geometry/ray.h"

class Sphere
{
public:
    Sphere(const Vector &centre, double radius, const Colour &colour);

    const Vector &centre() const;
    double radius() const;
    const Colour &colour() const;

    bool isHitBy(const Ray &ray) const;

private:
    Vector _centre;
    double _radius;
    Colour _colour;
};