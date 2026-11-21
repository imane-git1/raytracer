#pragma once

#include "geometry/hit.h"
#include "geometry/ray.h"
#include "geometry/shape.h"
#include "math/vector.h"

#include <memory>
#include <optional>
#include <vector>

class Scene
{
public:
    explicit Scene(const Vector &toLight);

    [[nodiscard]] const Vector &toLight() const;
    void add(std::unique_ptr<Shape> shape);
    [[nodiscard]] std::optional<Hit> nearestHit(const Ray &ray) const;

private:
    Vector _toLight;
    std::vector<std::unique_ptr<Shape>> _shapes;
};
