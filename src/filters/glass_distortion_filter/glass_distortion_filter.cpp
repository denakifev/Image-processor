#include "glass_distortion_filter.h"

#include "../base_filter.h"
#include "../../image/image.h"

#include <cstdint>
#include <random>

namespace image_processor::filters {

GlassDistortionFilter::GlassDistortionFilter(int distortion_strength)
    : distortion_strength_(distortion_strength), gen_(SEED) {
}

void GlassDistortionFilter::Apply(Image& image) const {

    std::uniform_int_distribution<int> dist(-distortion_strength_, distortion_strength_);

    std::vector<std::vector<Pixel>> new_pixels(image.GetHeight(), std::vector<Pixel>(image.GetWidth()));

    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            int new_i = i + dist(gen_);
            int new_j = j + dist(gen_);
            new_pixels[i][j] = BicubicInterpolation(image, new_i, new_j);
        }
    }

    image.SetPixels(std::move(new_pixels));
}

GlassDistortionFilter::~GlassDistortionFilter() {
}

float GlassDistortionFilter::BicubicKernel(float param) {
    constexpr float NegativeHalf = -0.5f;
    constexpr float ThreeHalves = 1.5f;
    constexpr float NegativeFiveHalves = -2.5f;
    constexpr float PositiveFiveHalves = 2.5f;
    constexpr float NegativeFour = -4.0f;
    constexpr float PositiveTwo = 2.0f;

    param = std::abs(param);
    if (param <= 1.0f) {
        return (ThreeHalves * param * param * param) + (NegativeFiveHalves * param * param) + 1.0f;
    } else if (param < PositiveTwo) {
        return (NegativeHalf * param * param * param) + (PositiveFiveHalves * param * param) + (NegativeFour * param) +
               PositiveTwo;
    }
    return 0.0f;
}

Pixel GlassDistortionFilter::BicubicInterpolation(const Image& image, int x, int y) const {
    int x0 = x;
    int y0 = y;
    Pixel new_pixel{};
    for (int di = -1; di < 2; ++di) {
        for (int dj = -1; dj < 2; ++dj) {
            int dx = x0 + di;
            int dy = y0 + dj;
            const Pixel current = image.At(dx, dy);
            float weight = BicubicKernel(static_cast<float>(x - dx)) * BicubicKernel(static_cast<float>(y - dy));
            new_pixel.red += current.red * weight;
            new_pixel.green += current.green * weight;
            new_pixel.blue += current.blue * weight;
        }
    }

    return new_pixel;
}

}  // namespace image_processor::filters