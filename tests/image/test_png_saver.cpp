#include <chrono>
#include <filesystem>
#include <string>
#include <system_error>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <stdexcept>
#include <lodepng.h>

#include "io/png_saver.h"

namespace
{
    class TemporaryDirectory
    {
    public:
        TemporaryDirectory()
            : _path(std::filesystem::temp_directory_path() /
                    ("raytracer-png-test-" +
                     std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())))
        {
            std::filesystem::create_directory(_path);
        }

        ~TemporaryDirectory()
        {
            std::error_code error;
            std::filesystem::remove_all(_path, error);
        }

        std::filesystem::path file(const std::string &name) const
        {
            return _path / name;
        }

    private:
        std::filesystem::path _path;
    };
}

TEST_CASE("a PNG saver writes the image to the requested path", "[image][png]")
{
    TemporaryDirectory directory;
    const std::filesystem::path outputPath = directory.file("custom-image.png");
    Image image(1, 1);
    image.setPixel(0, 0, Colour(1, 0.5, 0));

    PngSaver saver;
    saver.save(image, outputPath.string());

    std::vector<unsigned char> pixels;
    unsigned int width = 0;
    unsigned int height = 0;
    const std::string outputFilename = outputPath.string();
    const unsigned error = lodepng::decode(pixels, width, height, outputFilename.c_str());

    INFO("LodePNG decoding error: " << lodepng_error_text(error));
    REQUIRE(error == 0);
    REQUIRE(width == 1);
    REQUIRE(height == 1);
    REQUIRE((pixels == std::vector<unsigned char>{255, 128, 0, 255}));
}

TEST_CASE("a PNG saver writes the pixels row by row", "[image][png]")
{
    TemporaryDirectory directory;
    const std::filesystem::path outputPath = directory.file("rows.png");
    Image image(2, 2);
    image.setPixel(1, 0, Colour(1, 0.5, 0));

    PngSaver saver;
    saver.save(image, outputPath.string());

    std::vector<unsigned char> pixels;
    unsigned int width = 0;
    unsigned int height = 0;
    const std::string outputFilename = outputPath.string();
    const unsigned error = lodepng::decode(pixels, width, height, outputFilename.c_str());

    INFO("LodePNG decoding error: " << lodepng_error_text(error));
    REQUIRE(error == 0);
    REQUIRE((pixels == std::vector<unsigned char>{
        0, 0, 0, 255, 255, 128, 0, 255,
        0, 0, 0, 255, 0, 0, 0, 255
    }));
}

TEST_CASE("a PNG saver throws when the file cannot be written", "[image][png]")
{
  TemporaryDirectory directory;
  Image image(1, 1);
  PngSaver saver;

  REQUIRE_THROWS_AS(
      saver.save(image, directory.file("missing-folder/image.png").string()),
      std::runtime_error);
}