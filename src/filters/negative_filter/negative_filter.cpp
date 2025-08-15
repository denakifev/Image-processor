#include "negative_filter.h"
#include "../../image/image.h"

namespace image_processor::filters {

uint8_t NegativeFilter::GetNegative(float color) {
    return Pixel::ToByte(1.0f - color);
}

void NegativeFilter::Apply(Image& image) const {
    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            auto [blue, green, red] = image.GetPixel(i, j);
            image.SetPixel(i, j, Pixel(GetNegative(blue), GetNegative(green), GetNegative(red)));
        }
    }
}

NegativeFilter::~NegativeFilter() = default;
NegativeFilter::NegativeFilter() = default;

}  // namespace image_processor::filters