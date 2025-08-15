#include "negative_filter.h"
#include "../filter_maker.h"
#include "../base_filter.h"
#include "../../utils/utils.h"

#include <memory>

namespace image_processor::filters {

std::unique_ptr<BaseFilter> CreateNegativeFilterFromCmdArgs(const FilterDescriptor& fd) {
    return fd.GetFilterParamsCount() == 0 ? std::make_unique<NegativeFilter>() : nullptr;
}

}  // namespace image_processor::filters