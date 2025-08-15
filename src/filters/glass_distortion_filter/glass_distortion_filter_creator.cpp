#include "glass_distortion_filter.h"
#include "../filter_maker.h"
#include "../base_filter.h"
#include "../../utils/utils.h"

#include <cstdint>
#include <memory>

namespace image_processor::filters {

std::unique_ptr<BaseFilter> CreateGlassDistortionFilterFromCmdArgs(const FilterDescriptor& fd) {

    static const int GLASS_DISTORTION_FILTER_PARAMS_AMOUNT = 1;
    static const int STRENGTH_INDEX = 0;

    if (fd.GetFilterParamsCount() != GLASS_DISTORTION_FILTER_PARAMS_AMOUNT) {
        return nullptr;
    }

    auto& first_param = fd.filter_params[STRENGTH_INDEX];

    if (!utils::IsIntegerString(first_param)) {
        return nullptr;
    }

    int strength = std::stoi(first_param);

    return std::make_unique<GlassDistortionFilter>(strength);
}

}  // namespace image_processor::filters