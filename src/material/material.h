#pragma once

#include "colour/colour.h"
#include "math/vector.h"

class Material
{
public:
    explicit Material(const Colour &colour);

    [[nodiscard]] Colour colour() const;
    // normal and toLight must be unit vectors.
    [[nodiscard]] Colour shade(const Vector &normal, const Vector &toLight) const;

private:
    Colour _colour;
};
