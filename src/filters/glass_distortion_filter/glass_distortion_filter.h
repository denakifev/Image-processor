#pragma once

#include "../base_filter.h"
#include "../../image/image.h"

#include <cstdint>
#include <random>

namespace image_processor::filters {

class GlassDistortionFilter : public BaseFilter {
public:
    explicit GlassDistortionFilter(int distortion_strength);
    void Apply(Image& image) const override;
    ~GlassDistortionFilter() override;

protected:
    static float BicubicKernel(float param);
    Pixel BicubicInterpolation(const Image& image, int x, int y) const;
    int distortion_strength_;
    static const uint32_t SEED = 42;
    mutable std::mt19937 gen_;
};
}  // namespace image_processor::filters