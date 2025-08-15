#include "../src/filters/filters.h"

#include <catch.hpp>
#include <filesystem>

using namespace image_processor;
using image_processor::filters::GrayScaleFilter;

constexpr float Eps = 0.005f;

TEST_CASE("test_grayscale") {
    std::string test_picture = std::string(TEST_DATA_DIR) + "/flag.bmp";

    Image image(test_picture);
    GrayScaleFilter filter;
    filter.Apply(image);
    std::string grayscale_picture = std::string(TEST_DATA_DIR) + "/grayscale_flag.bmp";
    image.Save(grayscale_picture);

    std::string grayscale_canonical_result = std::string(TEST_DATA_DIR) + "/flag_gs.bmp";

    Image expected(grayscale_canonical_result);
    Image copy(grayscale_picture);

    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            auto copy_pixel = copy.GetPixel(i, j);
            auto expected_pixel = expected.GetPixel(i, j);
            REQUIRE(std::abs(copy_pixel.blue - expected_pixel.blue) < Eps);
            REQUIRE(std::abs(copy_pixel.green - expected_pixel.green) < Eps);
            REQUIRE(std::abs(copy_pixel.red - expected_pixel.red) < Eps);
        }
    }

    std::filesystem::remove(grayscale_picture);
}