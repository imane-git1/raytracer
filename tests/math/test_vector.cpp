#include <catch2/catch_test_macros.hpp>

#include "vector.h"

TEST_CASE("Vector addition") {
    const Vector first{1.0f, 2.0f, 3.0f};
    const Vector second{4.0f, 5.0f, 6.0f};

    const Vector result = first + second;

    REQUIRE(result.x() == 5.0f);
    REQUIRE(result.y() == 7.0f);
    REQUIRE(result.z() == 9.0f);
}

TEST_CASE("Vector subtraction") {
    const Vector first{-1.0f, 4.0f, 0.0f};
    const Vector second{-5.0f, 2.0f, 1.0f};

    const Vector result = first - second;

    REQUIRE(result.x() == 4.0f);
    REQUIRE(result.y() == 2.0f);
    REQUIRE(result.z() == -1.0f);
}
