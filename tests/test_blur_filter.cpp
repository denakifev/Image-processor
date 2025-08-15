#include "../src/filters/filters.h"

#include <catch.hpp>
#include <chrono>
#include <filesystem>

constexpr float Eps = 0.5f;
constexpr float TimeExpected = 22.0f;

using namespace image_processor;
using image_processor::filters::GaussianBlurFilter;

TEST_CASE("test_blur") {
    std::string test_picture = std::string(TEST_DATA_DIR) + "/lenna.bmp";
    std::string blur_picture = std::string(TEST_DATA_DIR) + "/blur_lenna.bmp";
    std::string canonical_blur_picture = std::string(TEST_DATA_DIR) + "/lenna_blur.bmp";
    GaussianBlurFilter filter(3.0f);

    Image image(test_picture);
    filter.Apply(image);
    image.Save(blur_picture);

    Image copy(blur_picture);
    Image expected(canonical_blur_picture);

    for (int i = 0; i < copy.GetHeight(); ++i) {
        for (int j = 0; j < copy.GetWidth(); ++j) {
            auto copy_pixel = copy.GetPixel(i, j);
            auto expected_pixel = expected.GetPixel(i, j);
            REQUIRE(std::abs(copy_pixel.blue - expected_pixel.blue) < Eps);
            REQUIRE(std::abs(copy_pixel.green - expected_pixel.green) < Eps);
            REQUIRE(std::abs(copy_pixel.red - expected_pixel.red) < Eps);
        }
    }

    std::filesystem::remove(blur_picture);
}

TEST_CASE("time") {
    auto start = std::chrono::high_resolution_clock::now();
    std::string test_picture = std::string(TEST_DATA_DIR) + "/lenna.bmp";
    GaussianBlurFilter filter(3.0f);
    Image image(test_picture);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    REQUIRE(elapsed.count() < TimeExpected);
}