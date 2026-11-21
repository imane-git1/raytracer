#include <stdexcept>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "image/image.h"
#include "colour/colour.h"
#include "math/vector.h"
#include "material/material.h"
#include "render/camera.h"
#include "scene/scene.h"
#include "test_helpers.h"

#include <memory>

TEST_CASE("a camera gives back its position", "[camera]")
{
  Camera camera(Vector(0, 0, -1), 2.0);

  requireVectorsEqual(camera.position(), Vector(0, 0, -1));
}

TEST_CASE("the centre ray starts at the camera and points along positive z", "[camera]")
{
  Camera camera(Vector(0, 0, -1), 2.0);

  Ray ray = camera.rayThroughPixel(0, 0, 1, 1);

  requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
  requireVectorsEqual(ray.direction(), Vector(0, 0, 1));
}

TEST_CASE("the centre pixel's ray goes through the screen centre", "[camera]")
{
  Camera camera(Vector(0, 0, -1), 2.0);

  Ray ray = camera.rayThroughPixel(1, 1, 3, 3);

  requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
  requireVectorsEqual(ray.direction(), Vector(0, 0, 1));
}

TEST_CASE("the top-left pixel's ray points to the top-left of the screen", "[camera]")
{
  Camera camera(Vector(0, 0, -1), 2.0);

  Ray ray = camera.rayThroughPixel(0, 0, 3, 3);

  requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
  requireVectorsEqual(ray.direction(), Vector(-2.0 / 3.0, 2.0 / 3.0, 1));
}

TEST_CASE("pixel rays point in the expected directions for a 5 by 3 image", "[camera]")
{
  Camera camera(Vector(0, 0, -1), 5.0);

  requireVectorsEqual(
      camera.rayThroughPixel(2, 1, 5, 3).direction(),
      Vector(0, 0, 1));
  requireVectorsEqual(
      camera.rayThroughPixel(4, 0, 5, 3).direction(),
      Vector(2, 1, 1));
  requireVectorsEqual(
      camera.rayThroughPixel(0, 2, 5, 3).direction(),
      Vector(-2, -1, 1));
}

TEST_CASE("pixel ray generation rejects invalid image dimensions and coordinates", "[camera]")
{
  Camera camera(Vector(0, 0, -1), 2.0);

  REQUIRE_THROWS_AS(camera.rayThroughPixel(0, 0, 0, 3), std::invalid_argument);
  REQUIRE_THROWS_AS(camera.rayThroughPixel(-1, 0, 3, 3), std::out_of_range);
}

TEST_CASE("a camera rejects a non-positive screen width", "[camera]")
{
  REQUIRE_THROWS_AS(Camera(Vector(0, 0, -1), 0.0), std::invalid_argument);
}

TEST_CASE("a 5 by 3 render of a sphere draws a red plus", "[camera]")
{
  Camera camera(Vector(0, 0, -1), 5.0);
  Scene scene(Vector(0, 0, -1));
  scene.add(std::make_unique<Sphere>(
      Vector(0, 0, 6), 5.0, Material(Colour(1, 0, 0))));

  Image image = camera.render(scene, 5, 3);

  const double expectedRed[3][5] = {
      {0, 0, 0.8, 0, 0},
      {0, 0.8, 1, 0.8, 0},
      {0, 0, 0.8, 0, 0},
  };
  for (int row = 0; row < 3; ++row)
  {
    for (int column = 0; column < 5; ++column)
    {
      Colour pixel = image.pixel(column, row);
      REQUIRE_THAT(pixel.r(), Catch::Matchers::WithinAbs(expectedRed[row][column], 1e-6));
      REQUIRE_THAT(pixel.g(), Catch::Matchers::WithinAbs(0.0, 1e-6));
      REQUIRE_THAT(pixel.b(), Catch::Matchers::WithinAbs(0.0, 1e-6));
    }
  }
}