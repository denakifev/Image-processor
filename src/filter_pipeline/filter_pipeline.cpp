#include "filter_pipeline.h"

#include <cstdint>

namespace image_processor {

void FilterPipeline::Apply(Image& image) const {
    for (const auto& filter : filters_) {
        filter->Apply(image);
    }
}

void FilterPipeline::AddFilter(std::unique_ptr<filters::BaseFilter> filter) {
    filters_.push_back(std::move(filter));
}

}  // namespace image_processor