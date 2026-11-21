#include "render/camera.h"
#include "render/trace.h"

#include <cmath>
#include <stdexcept>

Camera::Camera(const Vector &position, double screenWidth)
    : _position(position), _screenWidth(screenWidth)
{
    if (!std::isfinite(_screenWidth) || _screenWidth <= 0.0)
    {
        throw std::invalid_argument("Screen width must be a positive finite value");
    }
}

const Vector &Camera::position() const
{
    return _position;
}

Ray Camera::rayThroughPixel(int column, int row, int imageWidth, int imageHeight) const
{
    if (imageWidth <= 0 || imageHeight <= 0)
    {
        throw std::invalid_argument("Image dimensions must be positive");
    }
    if (column < 0 || column >= imageWidth || row < 0 || row >= imageHeight)
    {
        throw std::out_of_range("Pixel coordinates are outside the image");
    }

    double screenHeight = _screenWidth * imageHeight / imageWidth;
    double screenX = ((column + 0.5) / imageWidth - 0.5) * _screenWidth;
    double screenY = (0.5 - (row + 0.5) / imageHeight) * screenHeight;

    return Ray(_position, Vector(screenX, screenY, 1.0));
}

Image Camera::render(const Scene &scene, int width, int height) const
{
    Image image(width, height);

    for (int row = 0; row < height; ++row)
    {
        for (int column = 0; column < width; ++column)
        {
            Ray ray = rayThroughPixel(column, row, width, height);
            image.setPixel(column, row, trace(ray, scene));
        }
    }

    return image;
}