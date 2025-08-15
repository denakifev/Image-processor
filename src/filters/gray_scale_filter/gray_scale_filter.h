#pragma once

#include "../base_filter.h"

namespace image_processor::filters {

class GrayScaleFilter : public BaseFilter {
protected:
    static uint8_t GetConversion(float blue, float green, float red);

public:
    GrayScaleFilter();
    void Apply(Image& image) const override;
    ~GrayScaleFilter() override;
};

}  // namespace image_processor::filters