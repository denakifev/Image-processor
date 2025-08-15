#pragma once

#include "../base_filter.h"
#include "../../image/image.h"

namespace image_processor::filters {

class NegativeFilter : public BaseFilter {
protected:
    static uint8_t GetNegative(float color);

public:
    NegativeFilter();
    void Apply(Image& image) const override;
    ~NegativeFilter() override;
};

}  // namespace image_processor::filters