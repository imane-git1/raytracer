#pragma once

#include "geometry/hit.h"
#include "geometry/ray.h"
#include "geometry/shape.h"
#include "material/material.h"
#include "math/vector.h"

#include <optional>

class Plane : public Shape
{
public:
    Plane(const Vector &point, const Vector &normal, const Material &material);

    [[nodiscard]] std::optional<Hit> hit(const Ray &ray) const override;

private:
    Vector _point;
    Vector _normal;
    Material _material;
};
