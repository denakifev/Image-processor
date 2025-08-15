#pragma once

#include "../matrix_appling_filter.h"
#include "../../gray_scale_filter/gray_scale_filter.h"
#include "../../../image/image.h"

namespace image_processor::filters {

class EdgeDetectionFilter : public MatrixApplyingFilter {
protected:
    void SetMatrix() override;
    GrayScaleFilter gsfilter_;
    float threshold_;

public:
    explicit EdgeDetectionFilter(float threshold);
    void Apply(Image& image) const override;
    ~EdgeDetectionFilter() override;
};

}  // namespace image_processor::filters