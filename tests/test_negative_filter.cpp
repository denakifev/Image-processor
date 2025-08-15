#include "../src/filters/filters.h"

#include <catch.hpp>
#include <cmath>
#include <filesystem>

using namespace image_processor;
using image_processor::filters::NegativeFilter;

constexpr float Eps = 0.005f;

bool operator==(const Pixel& lhs, const Pixel& rhs) {
    return lhs.blue == rhs.blue && lhs.green == rhs.green && lhs.red == rhs.red;
}

TEST_CASE("test_negative") {
    std::string test_picture = std::string(TEST_DATA_DIR) + "/flag.bmp";

    Image image(test_picture);
    NegativeFilter filter;
    filter.Apply(image);
    std::string negative_picture = std::string(TEST_DATA_DIR) + "/negative_flag.bmp";
    image.Save(negative_picture);

    std::string negative_canonical_result = std::string(TEST_DATA_DIR) + "/flag_neg.bmp";

    Image expected(negative_canonical_result);
    Image copy(negative_picture);

    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            auto copy_pixel = copy.GetPixel(i, j);
            auto expected_pixel = expected.GetPixel(i, j);
            REQUIRE(std::abs(copy_pixel.blue - expected_pixel.blue) < Eps);
            REQUIRE(std::abs(copy_pixel.green - expected_pixel.green) < Eps);
            REQUIRE(std::abs(copy_pixel.red - expected_pixel.red) < Eps);
        }
    }

    std::filesystem::remove(negative_picture);
}