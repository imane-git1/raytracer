#include "image/image.h"

#include <stdexcept>

Image::Image(unsigned int width, unsigned int height)
    : _width(width),
      _height(height),
      _pixels(static_cast<std::size_t>(width) * height, Colour(0, 0, 0))
{
}

unsigned int Image::width() const { return _width; }
unsigned int Image::height() const { return _height; }

void Image::setPixel(unsigned int column, unsigned int row, const Colour &colour)
{
    _pixels.at(index(column, row)) = colour;
}

const Colour &Image::pixel(unsigned int column, unsigned int row) const
{
    return _pixels.at(index(column, row));
}

std::size_t Image::index(unsigned int column, unsigned int row) const
{
    if (column >= _width || row >= _height)
    {
        throw std::out_of_range("pixel coordinates are outside the image");
    }

    return static_cast<std::size_t>(row) * _width + column;
}