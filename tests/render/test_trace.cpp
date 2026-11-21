#include <catch2/catch_test_macros.hpp>

#include "colour/colour.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "math/vector.h"
#include "material/material.h"
#include "render/trace.h"
#include "scene/scene.h"
#include "test_helpers.h"

#include <memory>

TEST_CASE("trace shades a face-on hit with the full colour", "[trace]")
{
  Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
  Scene scene(Vector(0, 0, -1));
  scene.add(std::make_unique<Sphere>(
      Vector(0, 0, 9), 5, Material(Colour(1, 0, 0))));

  requireColoursEqual(trace(ray, scene), Colour(1, 0, 0));
}

TEST_CASE("trace shades a hit at the 3-4-5 angle", "[trace]")
{
  Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
  Scene scene(Vector(0.6, 0, -0.8));
  scene.add(std::make_unique<Sphere>(
      Vector(0, 0, 9), 5, Material(Colour(1, 0, 0))));

  requireColoursEqual(trace(ray, scene), Colour(0.8, 0, 0));
}

TEST_CASE("trace shades a side hit", "[trace]")
{
  Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
  Scene scene(Vector(0, 0, -1));
  scene.add(std::make_unique<Sphere>(
      Vector(3, 0, 9), 5, Material(Colour(1, 0, 0))));

  requireColoursEqual(trace(ray, scene), Colour(0.8, 0, 0));
}

TEST_CASE("trace gives black when the ray misses the sphere", "[trace]")
{
  Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
  Scene scene(Vector(0, 0, -1));
  scene.add(std::make_unique<Sphere>(
      Vector(6, 0, 9), 5, Material(Colour(1, 0, 0))));

  requireColoursEqual(trace(ray, scene), Colour(0, 0, 0));
}