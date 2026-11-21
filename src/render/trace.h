#pragma once

#include "colour/colour.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "math/vector.h"
#include "scene/scene.h"

[[nodiscard]] Colour trace(const Ray &ray, const Scene &scene);