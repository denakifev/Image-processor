#pragma once

#include "../image/image.h"

namespace image_processor::filters {

class BaseFilter {
public:
    virtual void Apply(Image& image) const = 0;
    virtual ~BaseFilter() = 0;
};

}  // namespace image_processor::filters