#include "matrix_appling_filter.h"
#include "../../image/image.h"

#include <algorithm>

namespace image_processor::filters {

void MatrixApplyingFilter::SetMatrix() {
}
void MatrixApplyingFilter::Apply(Image& image) const {
    std::vector<std::vector<Pixel>> new_pixels(image.GetHeight(), std::vector<Pixel>(image.GetWidth()));

    for (size_t i = 0; i < image.GetHeight(); i++) {
        for (size_t j = 0; j < image.GetWidth(); j++) {
            new_pixels[i][j] = ModifyPixel(i, j, image);
        }
    }

    image.SetPixels(std::move(new_pixels));
}

Pixel MatrixApplyingFilter::ModifyPixel(size_t i, size_t j, const Image& image) const {
    int filter_size = static_cast<int>(matrix_.size());
    int half_size = filter_size / 2;
    Pixel new_pixel{};

    for (int di = -half_size; di <= half_size; ++di) {
        for (int dj = -half_size; dj <= half_size; ++dj) {
            Pixel p = image.At(static_cast<int32_t>(i + di), static_cast<int32_t>(j + dj));
            float weight = matrix_[di + half_size][dj + half_size];

            new_pixel.red += p.red * weight;
            new_pixel.green += p.green * weight;
            new_pixel.blue += p.blue * weight;
        }
    }

    new_pixel.blue = std::clamp(new_pixel.blue, 0.0f, 1.0f);
    new_pixel.green = std::clamp(new_pixel.green, 0.0f, 1.0f);
    new_pixel.red = std::clamp(new_pixel.red, 0.0f, 1.0f);

    return new_pixel;
}

}  // namespace image_processor::filters
