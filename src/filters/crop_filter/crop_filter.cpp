#include "crop_filter.h"
#include "../../image/image.h"

#include <cstdint>

namespace image_processor::filters {

CropFilter::~CropFilter() = default;

CropFilter::CropFilter(int32_t width, int32_t height) : width_(width), height_(height) {
}

void CropFilter::Apply(Image& image) const {
    image.SetHeight(height_);
    image.SetWidth(width_);
}

}  // namespace image_processor::filters
