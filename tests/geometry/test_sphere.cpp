#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "colour/colour.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "math/vector.h"
#include "material/material.h"
#include "test_helpers.h"

TEST_CASE("a sphere gives a front hit with point normal and material", "[sphere]")
{
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 9), 5, Material(Colour(1, 0, 0)));

    std::optional<Hit> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, Catch::Matchers::WithinAbs(5, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 0, 4));
    requireVectorsEqual(hit->normal, Vector(0, 0, -1));
    requireColoursEqual(hit->material.colour(), Colour(1, 0, 0));
}

TEST_CASE("a side sphere hit gives the 3-4-5 normal", "[sphere]")
{
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(3, 0, 9), 5, Material(Colour(1, 0, 0)));

    std::optional<Hit> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, Catch::Matchers::WithinAbs(6, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 0, 5));
    requireVectorsEqual(hit->normal, Vector(-0.6, 0, -0.8));
}

TEST_CASE("a sphere beside the ray has no hit", "[sphere]")
{
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(6, 0, 9), 5, Material(Colour(1, 0, 0)));

    REQUIRE_FALSE(sphere.hit(ray).has_value());
}

TEST_CASE("a sphere behind the ray has no hit", "[sphere]")
{
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, -11), 5, Material(Colour(1, 0, 0)));

    REQUIRE_FALSE(sphere.hit(ray).has_value());
}

TEST_CASE("a ray starting inside a sphere exits at the far hit", "[sphere]")
{
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 1), 5, Material(Colour(1, 0, 0)));

    std::optional<Hit> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, Catch::Matchers::WithinAbs(7, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 0, 6));
    requireVectorsEqual(hit->normal, Vector(0, 0, 1));
}