#pragma once

#include "../filters/filters.h"
#include "../image/image.h"

#include <cstdint>
#include <memory>

namespace image_processor {

class FilterPipeline {
public:
    using FilterCollection = std::vector<std::unique_ptr<filters::BaseFilter>>;

    void AddFilter(std::unique_ptr<filters::BaseFilter> filter);

    void Apply(Image& image) const;

protected:
    FilterCollection filters_;
};

}  // namespace image_processor