#include "edge_detection_filter.h"
#include "../../../image/image.h"

namespace image_processor::filters {

EdgeDetectionFilter::EdgeDetectionFilter(float threshold) : threshold_(threshold) {
    SetMatrix();
};

EdgeDetectionFilter::~EdgeDetectionFilter() = default;

void EdgeDetectionFilter::SetMatrix() {
    constexpr float EdgeCenter = 4.0f;
    constexpr float EdgeAdjacent = -1.0f;
    constexpr float EdgeCorner = 0.0f;

    matrix_ = {{EdgeCorner, EdgeAdjacent, EdgeCorner},
               {EdgeAdjacent, EdgeCenter, EdgeAdjacent},
               {EdgeCorner, EdgeAdjacent, EdgeCorner}};
}

void EdgeDetectionFilter::Apply(Image& image) const {
    static const uint8_t WHITE = 255;
    static const uint8_t BLACK = 0;
    gsfilter_.Apply(image);
    MatrixApplyingFilter::Apply(image);
    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            auto [blue, green, red] = image.GetPixel(i, j);
            if (blue > threshold_) {
                image.SetPixel(i, j, Pixel(WHITE, WHITE, WHITE));
            } else {
                image.SetPixel(i, j, Pixel(BLACK, BLACK, BLACK));
            }
        }
    }
}

}  // namespace image_processor::filters
