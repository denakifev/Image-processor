#pragma once

#include "../base_filter.h"
#include "../../image/image.h"

#include <cstdint>

namespace image_processor::filters {

class CropFilter : public BaseFilter {
protected:
    int32_t width_;
    int32_t height_;

public:
    CropFilter(int32_t width, int32_t height);
    void Apply(Image& image) const override;
    ~CropFilter() override;
};

}  // namespace image_processor::filters