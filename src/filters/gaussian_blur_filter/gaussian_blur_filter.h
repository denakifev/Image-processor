#pragma once

#include "../base_filter.h"
#include "../../image/image.h"

#include <vector>

namespace image_processor::filters {

class GaussianBlurFilter : public BaseFilter {
protected:
    enum class Direction { HORIZONTAL, VERTICAL };
    float sigma_;
    int radius_;
    std::vector<float> kernel_;
    void GenKernel();
    void ApplyBlur(Image& image, Direction direction) const;

public:
    explicit GaussianBlurFilter(float sigma);
    ~GaussianBlurFilter() override;
    void Apply(Image& image) const override;
};

}  // namespace image_processor::filters
