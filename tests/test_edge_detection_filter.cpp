#include "../src/filters/filters.h"

#include <catch.hpp>
#include <filesystem>

using namespace image_processor;
using image_processor::filters::EdgeDetectionFilter;

bool operator==(const Pixel& lhs, const Pixel& rhs) {
    return lhs.blue == rhs.blue && lhs.green == rhs.green && lhs.red == rhs.red;
}

TEST_CASE("test_edge_detection") {
    std::string test_picture = std::string(TEST_DATA_DIR) + "/flag.bmp";
    std::string edge_picture = std::string(TEST_DATA_DIR) + "/edge_flag.bmp";
    std::string edge_canonical_result = std::string(TEST_DATA_DIR) + "/flag_edge.bmp";
    EdgeDetectionFilter filter(0.1f);
    Image image(test_picture);
    filter.Apply(image);
    image.Save(edge_picture);

    Image copy(edge_picture);
    Image expected(edge_canonical_result);

    for (int i = 0; i < copy.GetHeight(); ++i) {
        for (int j = 0; j < copy.GetWidth(); ++j) {
            auto copy_pixel = copy.GetPixel(i, j);
            auto expected_pixel = expected.GetPixel(i, j);
            REQUIRE(::operator==(copy_pixel, expected_pixel));
        }
    }

    std::filesystem::remove(edge_picture);
}