#include <catch2/catch_test_macros.hpp>

#include "material/material.h"
#include "math/vector.h"
#include "test_helpers.h"

TEST_CASE("a material gives back its colour", "[material]")
{
    Material material(Colour(1, 0.5, 0));

    requireColoursEqual(material.colour(), Colour(1, 0.5, 0));
}

TEST_CASE("a material takes the whole colour when face-on to the light", "[material]")
{
    Material material(Colour(1, 0.5, 0));

    requireColoursEqual(
        material.shade(Vector(0, 0, -1), Vector(0, 0, -1)),
        Colour(1, 0.5, 0));
}

TEST_CASE("a material scales the colour at the 3-4-5 angle", "[material]")
{
    Material material(Colour(1, 0.5, 0));

    requireColoursEqual(
        material.shade(Vector(0, 0, -1), Vector(0.6, 0, -0.8)),
        Colour(0.8, 0.4, 0));
}

TEST_CASE("a material is black when it faces away sideways", "[material]")
{
    Material material(Colour(1, 0.5, 0));

    requireColoursEqual(
        material.shade(Vector(0, 0, -1), Vector(1, 0, 0)),
        Colour(0, 0, 0));
}

TEST_CASE("a material is black when it faces away from the light", "[material]")
{
    Material material(Colour(1, 0.5, 0));

    requireColoursEqual(
        material.shade(Vector(0, 0, -1), Vector(0, 0, 1)),
        Colour(0, 0, 0));
}
