#include "../src/filters/filters.h"

#include <catch.hpp>
#include <filesystem>
#include <vector>

using namespace image_processor;
using image_processor::filters::CropFilter;

bool operator==(const Pixel& lhs, const Pixel& rhs) {
    return lhs.blue == rhs.blue && lhs.green == rhs.green && lhs.red == rhs.red;
}

TEST_CASE("test crop") {
    std::vector<std::pair<int, int>> valid_args = {{1, 1}, {10, 10}, {5, 10}, {7, 13}, {30, 30}};

    for (const auto& [width, height] : valid_args) {
        std::string test_picture = std::string(TEST_DATA_DIR) + "/flag.bmp";
        Image image(test_picture);

        CropFilter crop_filter(width, height);
        crop_filter.Apply(image);
        REQUIRE(image.GetWidth() <= width);
        REQUIRE(image.GetHeight() <= height);

        std::string filename = std::string(TEST_DATA_DIR) + "/crop_tmp" + ".bmp";
        image.Save(filename);
        Image copy(filename);

        REQUIRE(copy.GetWidth() <= width);
        REQUIRE(copy.GetHeight() <= height);

        Image old_image(test_picture);

        for (int i = 0; i < copy.GetHeight(); ++i) {
            for (int j = 0; j < copy.GetWidth(); ++j) {
                REQUIRE(::operator==(old_image.GetPixel(i, j), copy.GetPixel(i, j)));
            }
        }

        std::filesystem::remove(filename);
    }
}