#pragma once

#include <string>

#include "image/image_saver.h"

class PngSaver : public ImageSaver
{
public:
    void save(const Image &image, const std::string &outputPath) override;
};
