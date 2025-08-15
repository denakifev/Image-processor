#include "../src/filters/filters.h"

#include <catch.hpp>
#include <filesystem>

using namespace image_processor;
using image_processor::filters::SharpFilter;

bool operator==(const Pixel& lhs, const Pixel& rhs) {
    return lhs.blue == rhs.blue && lhs.green == rhs.green && lhs.red == rhs.red;
}

TEST_CASE("test_sharp_filter") {
    std::string test_picture = std::string(TEST_DATA_DIR) + "/flag.bmp";
    std::string sharp_picture = std::string(TEST_DATA_DIR) + "/sharp_flag.bmp";
    std::string sharp_canonical_result = std::string(TEST_DATA_DIR) + "/flag_sharp.bmp";

    Image image(test_picture);
    SharpFilter filter;

    filter.Apply(image);

    image.Save(sharp_picture);

    Image expected(sharp_canonical_result);
    Image copy(sharp_picture);

    for (int i = 0; i < copy.GetHeight(); ++i) {
        for (int j = 0; j < copy.GetWidth(); ++j) {
            auto copy_pixel = copy.GetPixel(i, j);
            auto expected_pixel = expected.GetPixel(i, j);
            REQUIRE(::operator==(copy_pixel, expected_pixel));
        }
    }

    std::filesystem::remove(sharp_picture);
}
