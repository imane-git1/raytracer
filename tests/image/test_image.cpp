#include <catch2/catch_test_macros.hpp>
#include <stdexcept>

#include "image/image.h"
#include "test_helpers.h"

TEST_CASE("setting a pixel uses column and row coordinates", "[image]")
{
  Image image(5, 4);
  const Colour black(0, 0, 0);
  const Colour red(1, 0, 0);

  image.setPixel(3, 2, red);

  REQUIRE(image.width() == 5);
  REQUIRE(image.height() == 4);

  for (unsigned int row = 0; row < image.height(); ++row)
  {
    for (unsigned int column = 0; column < image.width(); ++column)
    {
      const Colour &expected = (column == 3 && row == 2) ? red : black;
      requireColoursEqual(image.pixel(column, row), expected);
    }
  }
}

TEST_CASE("a pixel outside the image cannot be read or written", "[image]")
{
  Image image(5, 4);

  REQUIRE_THROWS_AS(image.pixel(5, 0), std::out_of_range);
  REQUIRE_THROWS_AS(image.pixel(0, 4), std::out_of_range);
  REQUIRE_THROWS_AS(image.setPixel(5, 0, Colour(1, 0, 0)), std::out_of_range);
}
