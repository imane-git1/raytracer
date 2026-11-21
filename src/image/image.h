#pragma once

#include <cstddef>
#include <vector>

#include "colour/colour.h"

class Image
{
public:
    Image(unsigned int width, unsigned int height);

    [[nodiscard]] unsigned int width() const;
    [[nodiscard]] unsigned int height() const;

    void setPixel(unsigned int column, unsigned int row, const Colour &colour);
    [[nodiscard]] const Colour &pixel(unsigned int column, unsigned int row) const;

private:
    std::size_t index(unsigned int column, unsigned int row) const;

    unsigned int _width;
    unsigned int _height;
    std::vector<Colour> _pixels;
};