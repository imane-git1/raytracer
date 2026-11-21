#pragma once

#include <string>

#include "image/image.h"

class ImageSaver
{
public:
    virtual ~ImageSaver() = default;

    // Writes the whole image to outputPath and leaves the image unchanged.
    // Throws std::runtime_error if the file cannot be written.
    virtual void save(const Image &image, const std::string &outputPath) = 0;
};
