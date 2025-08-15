#include "gray_scale_filter.h"

#include <stdexcept>

namespace image_processor::filters {

GrayScaleFilter::GrayScaleFilter() = default;
GrayScaleFilter::~GrayScaleFilter() = default;

uint8_t GrayScaleFilter::GetConversion(float blue, float green, float red) {
    constexpr float RedWeight = 0.299f;
    constexpr float GreenWeight = 0.587f;
    constexpr float BlueWeight = 0.114f;

    return Pixel::ToByte(RedWeight * red + GreenWeight * green + BlueWeight * blue);
}

void GrayScaleFilter::Apply(Image& image) const {
    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            auto [blue, green, red] = image.GetPixel(i, j);
            uint8_t conversion = GetConversion(blue, green, red);
            image.SetPixel(i, j, Pixel(conversion, conversion, conversion));
        }
    }
}

}  // namespace image_processor::filters
