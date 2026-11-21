#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "geometry/plane.h"
#include "geometry/ray.h"
#include "material/material.h"
#include "test_helpers.h"

TEST_CASE("a ray hits the 3D floor", "[plane]")
{
    Plane plane(Vector(0, 0, 0), Vector(0, 1, 0), Material(Colour(0, 1, 0)));
    Ray ray(Vector(0, 8, 0), Vector(3, -4, 0));

    std::optional<Hit> hit = plane.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, Catch::Matchers::WithinAbs(2, tolerance));
    requireVectorsEqual(hit->point, Vector(6, 0, 0));
    requireVectorsEqual(hit->normal, Vector(0, 1, 0));
    requireColoursEqual(hit->material.colour(), Colour(0, 1, 0));
}

TEST_CASE("a ray hits a plane with a non-axis normal", "[plane]")
{
    Plane plane(Vector(8, 0, 0), Vector(3, 4, 0), Material(Colour(0, 1, 0)));
    Ray ray(Vector(-8, 0, 0), Vector(4, 3, 0));

    std::optional<Hit> hit = plane.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, Catch::Matchers::WithinAbs(2, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 6, 0));
    requireVectorsEqual(hit->normal, Vector(0.6, 0.8, 0));
}

TEST_CASE("a ray parallel to the floor misses", "[plane]")
{
    Plane plane(Vector(0, 0, 0), Vector(0, 1, 0), Material(Colour(0, 1, 0)));
    Ray ray(Vector(0, 8, 0), Vector(5, 0, 0));

    REQUIRE_FALSE(plane.hit(ray).has_value());
}

TEST_CASE("a floor behind the ray misses", "[plane]")
{
    Plane plane(Vector(0, 0, 0), Vector(0, 1, 0), Material(Colour(0, 1, 0)));
    Ray ray(Vector(0, 8, 0), Vector(3, 4, 0));

    REQUIRE_FALSE(plane.hit(ray).has_value());
}
