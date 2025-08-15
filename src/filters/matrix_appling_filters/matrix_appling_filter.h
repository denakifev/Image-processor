#pragma once

#include "../base_filter.h"
#include "../../image/image.h"

#include <vector>

namespace image_processor::filters {

class MatrixApplyingFilter : public BaseFilter {
protected:
    std::vector<std::vector<float>> matrix_;
    virtual void SetMatrix() = 0;
    Pixel ModifyPixel(size_t i, size_t j, const Image& image) const;

public:
    void Apply(Image& image) const override;
};

}  // namespace image_processor::filters