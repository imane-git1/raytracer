#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "geometry/plane.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "scene/scene.h"
#include "test_helpers.h"

#include <memory>

TEST_CASE("a scene stores the sun as a unit vector", "[scene]")
{
    Scene scene(Vector(0, 3, -4));

    requireVectorsEqual(scene.toLight(), Vector(0, 0.6, -0.8));
}

TEST_CASE("a closer plane wins when added after a sphere", "[scene]")
{
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(
        Vector(0, 0, 9), 5, Material(Colour(1, 0, 0))));
    scene.add(std::make_unique<Plane>(
        Vector(0, 0, 2), Vector(0, 0, -1), Material(Colour(0, 0, 1))));

    std::optional<Hit> hit = scene.nearestHit(
        Ray(Vector(0, 0, -1), Vector(0, 0, 1)));

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, Catch::Matchers::WithinAbs(3, tolerance));
    requireColoursEqual(hit->material.colour(), Colour(0, 0, 1));
}

TEST_CASE("a farther plane loses when added after a sphere", "[scene]")
{
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(
        Vector(0, 0, 9), 5, Material(Colour(1, 0, 0))));
    scene.add(std::make_unique<Plane>(
        Vector(0, 0, 20), Vector(0, 0, -1), Material(Colour(0, 0, 1))));

    std::optional<Hit> hit = scene.nearestHit(
        Ray(Vector(0, 0, -1), Vector(0, 0, 1)));

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, Catch::Matchers::WithinAbs(5, tolerance));
    requireColoursEqual(hit->material.colour(), Colour(1, 0, 0));
}

TEST_CASE("only a miss gives no nearest hit", "[scene]")
{
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(
        Vector(6, 0, 9), 5, Material(Colour(1, 0, 0))));

    REQUIRE_FALSE(scene.nearestHit(
        Ray(Vector(0, 0, -1), Vector(0, 0, 1)))
        .has_value());
}

TEST_CASE("a closer plane wins when added before a sphere", "[scene]")
{
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Plane>(
        Vector(0, 0, 2), Vector(0, 0, -1), Material(Colour(0, 0, 1))));
    scene.add(std::make_unique<Sphere>(
        Vector(0, 0, 9), 5, Material(Colour(1, 0, 0))));

    std::optional<Hit> hit = scene.nearestHit(
        Ray(Vector(0, 0, -1), Vector(0, 0, 1)));

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, Catch::Matchers::WithinAbs(3, tolerance));
    requireColoursEqual(hit->material.colour(), Colour(0, 0, 1));
}

TEST_CASE("a farther plane loses when added before a sphere", "[scene]")
{
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Plane>(
        Vector(0, 0, 20), Vector(0, 0, -1), Material(Colour(0, 0, 1))));
    scene.add(std::make_unique<Sphere>(
        Vector(0, 0, 9), 5, Material(Colour(1, 0, 0))));

    std::optional<Hit> hit = scene.nearestHit(
        Ray(Vector(0, 0, -1), Vector(0, 0, 1)));

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, Catch::Matchers::WithinAbs(5, tolerance));
    requireColoursEqual(hit->material.colour(), Colour(1, 0, 0));
}
