#include "gaussian_blur_filter.h"
#include "../filter_maker.h"
#include "../base_filter.h"
#include "../../utils/utils.h"

#include <memory>

namespace image_processor::filters {

std::unique_ptr<BaseFilter> CreateGaussianBlurFilterFromCmdArgs(const FilterDescriptor& fd) {
    static const int GAUSSIAN_BLUR_FILTER_PARAMS_AMOUNT = 1;
    static const int SIGMA_INDEX = 0;

    if (fd.GetFilterParamsCount() != GAUSSIAN_BLUR_FILTER_PARAMS_AMOUNT) {
        return nullptr;
    }

    auto& first_param = fd.filter_params[SIGMA_INDEX];

    if (!utils::IsFloatString(first_param)) {
        return nullptr;
    }

    float sigma = std::stof(first_param);

    return std::make_unique<GaussianBlurFilter>(sigma);
}

}  // namespace image_processor::filters