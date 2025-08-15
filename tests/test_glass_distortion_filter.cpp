#include "../src/filters/filters.h"

#include <catch.hpp>
#include <filesystem>

using namespace image_processor;
using image_processor::filters::GlassDistortionFilter;

constexpr float Eps = 1.0f;

TEST_CASE("test_grayscale") {
    std::string test_picture = std::string(TEST_DATA_DIR) + "/lenna.bmp";

    Image image(test_picture);
    GlassDistortionFilter filter(30);
    filter.Apply(image);
    std::string glass_picture = std::string(TEST_DATA_DIR) + "/glass_lenna.bmp";
    image.Save(glass_picture);

    std::string glass_canonical_result = std::string(TEST_DATA_DIR) + "/lenna_glass.bmp";

    Image expected(glass_canonical_result);
    Image copy(glass_picture);

    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            auto copy_pixel = copy.GetPixel(i, j);
            auto expected_pixel = expected.GetPixel(i, j);
            REQUIRE(std::abs(copy_pixel.blue - expected_pixel.blue) < Eps);
            REQUIRE(std::abs(copy_pixel.green - expected_pixel.green) < Eps);
            REQUIRE(std::abs(copy_pixel.red - expected_pixel.red) < Eps);
        }
    }

    std::filesystem::remove(glass_picture);
}