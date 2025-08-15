#include "gaussian_blur_filter.h"

#include <cmath>

namespace image_processor::filters {

GaussianBlurFilter::GaussianBlurFilter(float sigma) : sigma_(sigma) {
    GenKernel();
}

void GaussianBlurFilter::ApplyBlur(Image& image, GaussianBlurFilter::Direction direction) const {
    int width = image.GetWidth();
    int height = image.GetHeight();
    int major = direction == Direction::HORIZONTAL ? width : height;
    int minor = direction == Direction::HORIZONTAL ? height : width;
    for (int i = 0; i < minor; ++i) {
        std::vector<Pixel> temp;
        temp.reserve(major);
        for (int j = 0; j < major; ++j) {
            float red = 0.0f;
            float green = 0.0f;
            float blue = 0.0f;
            float weight_sum = 0.0f;

            for (int k = -radius_; k <= radius_; ++k) {
                int index = j + k;
                const Pixel& p = direction == Direction::HORIZONTAL ? image.At(index, i) : image.At(i, index);
                float weight = kernel_[k + radius_];
                red += p.red * weight;
                green += p.green * weight;
                blue += p.blue * weight;
                weight_sum += weight;
            }

            temp.emplace_back(Pixel::ToByte(blue / weight_sum), Pixel::ToByte(green / weight_sum),
                              Pixel::ToByte(red / weight_sum));
        }
        for (int j = 0; j < major; ++j) {
            if (direction == Direction::HORIZONTAL) {
                image.SetPixel(j, i, temp[j]);
            } else {
                image.SetPixel(i, j, temp[j]);
            }
        }
    }
}

void GaussianBlurFilter::GenKernel() {
    kernel_.clear();
    constexpr float Half = 0.5f;
    radius_ = static_cast<int>(std::ceil(3 * sigma_));
    int kernel_size = 2 * radius_ + 1;
    kernel_.reserve(kernel_size);
    float sum = 0.0f;

    for (int i = -radius_; i <= radius_; ++i) {
        kernel_[i + radius_] = std::exp(-Half * static_cast<float>(i * i) / (sigma_ * sigma_));
        sum += kernel_[i + radius_];
    }

    for (int i = 0; i < kernel_size; ++i) {
        kernel_[i] /= sum;
    }
}

void GaussianBlurFilter::Apply(Image& image) const {
    ApplyBlur(image, GaussianBlurFilter::Direction::HORIZONTAL);
    ApplyBlur(image, GaussianBlurFilter::Direction::VERTICAL);
}

GaussianBlurFilter::~GaussianBlurFilter() = default;

}  // namespace image_processor::filters