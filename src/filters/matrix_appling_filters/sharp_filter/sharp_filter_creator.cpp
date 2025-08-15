#include "sharp_filter.h"
#include "../../filter_maker.h"
#include "../../base_filter.h"
#include "../../../utils/utils.h"

#include <memory>

namespace image_processor::filters {

std::unique_ptr<BaseFilter> CreateSharpFilterFromCmdArgs(const FilterDescriptor& fd) {
    return fd.GetFilterParamsCount() == 0 ? std::make_unique<SharpFilter>() : nullptr;
}

}  // namespace image_processor::filters