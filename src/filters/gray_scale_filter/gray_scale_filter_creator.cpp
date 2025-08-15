#include "gray_scale_filter.h"
#include "../filter_maker.h"
#include "../base_filter.h"
#include "../../utils/utils.h"

#include <memory>

namespace image_processor::filters {

std::unique_ptr<BaseFilter> CreateGrayscaleFilterFromCmdArgs(const FilterDescriptor& fd) {
    return fd.GetFilterParamsCount() == 0 ? std::make_unique<GrayScaleFilter>() : nullptr;
}

}  // namespace image_processor::filters