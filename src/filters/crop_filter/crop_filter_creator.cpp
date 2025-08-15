#include "crop_filter.h"
#include "../filter_maker.h"
#include "../base_filter.h"
#include "../../utils/utils.h"

#include <cstdint>
#include <memory>

namespace image_processor::filters {

std::unique_ptr<BaseFilter> CreateCropFilterFromCmdArgs(const FilterDescriptor& fd) {

    static const int CROP_FILTER_PARAMS_AMOUNT = 2;
    static const int WIDTH_INDEX = 0;
    static const int HEIGHT_INDEX = 1;

    if (fd.GetFilterParamsCount() != CROP_FILTER_PARAMS_AMOUNT) {
        return nullptr;
    }

    auto& first_param = fd.filter_params[WIDTH_INDEX];
    auto& second_param = fd.filter_params[HEIGHT_INDEX];

    if (!utils::IsIntegerString(first_param) || !utils::IsIntegerString(second_param)) {
        return nullptr;
    }

    int32_t width = std::stoi(first_param);
    int32_t height = std::stoi(second_param);

    return std::make_unique<CropFilter>(width, height);
}

}  // namespace image_processor::filters