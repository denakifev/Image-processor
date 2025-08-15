#include <catch.hpp>
#include <filesystem>

#include "../src/image/image.h"

using namespace image_processor;

bool operator==(const Pixel& lhs, const Pixel& rhs) {
    return lhs.blue == rhs.blue && lhs.green == rhs.green && lhs.red == rhs.red;
}

TEST_CASE("Read Invalide file") {
    REQUIRE_THROWS_AS(Image("invalid_file.bmp"), std::runtime_error);
}

TEST_CASE("Read valid file") {
    Image image(std::string(TEST_DATA_DIR) + "/flag.bmp");
    REQUIRE(image.GetWidth() == 10);
    REQUIRE(image.GetHeight() == 20);
}

TEST_CASE("Write file") {
    Pixel black(0, 0, 0);
    std::string test_picture = std::string(TEST_DATA_DIR) + "/flag.bmp";
    std::string copy_picture = std::string(TEST_DATA_DIR) + "/flag_copy.bmp";
    std::string modified_picture = std::string(TEST_DATA_DIR) + "/flag_modified.bmp";
    Image image(test_picture);
    image.Save(copy_picture);

    Image copy(copy_picture);
    REQUIRE(copy.GetWidth() == image.GetWidth());
    REQUIRE(copy.GetHeight() == image.GetHeight());
    for (int i = 0; i < copy.GetHeight(); ++i) {
        for (int j = 0; j < copy.GetWidth(); ++j) {
            REQUIRE(::operator==(image.GetPixel(i, j), copy.GetPixel(i, j)));
        }
    }

    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            image.SetPixel(i, j, black);
        }
    }

    image.Save(modified_picture);

    Image copy2(modified_picture);

    for (int i = 0; i < copy2.GetHeight(); ++i) {
        for (int j = 0; j < copy2.GetWidth(); ++j) {
            REQUIRE(::operator==(image.GetPixel(i, j), copy2.GetPixel(i, j)));
        }
    }

    std::filesystem::remove(copy_picture);
    std::filesystem::remove(modified_picture);
}
