#pragma once

#include "material/material.h"
#include "math/vector.h"

struct Hit
{
    double t = 0.0;
    Vector point;
    Vector normal;
    Material material;
};
