#include <stdexcept>

#include <catch2/catch_test_macros.hpp>

#include "geometry/ray.h"
#include "math/vector.h"
#include "render/camera.h"
#include "test_helpers.h"

TEST_CASE("a camera gives back its position", "[camera]")
{
  Camera camera(Vector(0, 0, -1), 2.0);

  requireVectorsEqual(camera.position(), Vector(0, 0, -1));
}

TEST_CASE("the centre ray starts at the camera and points along positive z", "[camera]")
{
  Camera camera(Vector(0, 0, -1), 2.0);

  Ray ray = camera.rayThroughCentre();

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