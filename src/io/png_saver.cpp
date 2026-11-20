#include "io/png_saver.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>

#include "lodepng.h"

namespace
{
    unsigned char toByte(double channel)
    {
        return static_cast<unsigned char>(std::lround(std::clamp(channel, 0.0, 1.0) * 255.0));
    }

    std::vector<unsigned char> toRgbaBytes(const Image &image)
    {
        std::vector<unsigned char> bytes;
        bytes.reserve(static_cast<std::size_t>(image.width()) * image.height() * 4);

        for (unsigned int row = 0; row < image.height(); ++row)
        {
            for (unsigned int column = 0; column < image.width(); ++column)
            {
                const Colour &colour = image.pixel(column, row);
                bytes.push_back(toByte(colour.r()));
                bytes.push_back(toByte(colour.g()));
                bytes.push_back(toByte(colour.b()));
                bytes.push_back(255);
            }
        }

        return bytes;
    }
}

void PngSaver::save(const Image &image, const std::string &outputPath)
{
    const unsigned error =
        lodepng::encode(outputPath.c_str(), toRgbaBytes(image), image.width(), image.height());
    if (error != 0)
    {
        throw std::runtime_error(
            "could not encode PNG '" + outputPath + "': " + lodepng_error_text(error));
    }
}