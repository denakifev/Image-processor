#include "sharp_filter.h"

namespace image_processor::filters {

void SharpFilter::SetMatrix() {
    constexpr float SharpCenter = 5.0f;
    constexpr float SharpAdjacent = -1.0f;
    constexpr float SharpCorner = 0.0f;

    matrix_ = {{SharpCorner, SharpAdjacent, SharpCorner},
               {SharpAdjacent, SharpCenter, SharpAdjacent},
               {SharpCorner, SharpAdjacent, SharpCorner}};
}

SharpFilter::SharpFilter() {
    SetMatrix();
}

SharpFilter::~SharpFilter() = default;

}  // namespace image_processor::filters
