#include "edge_detection_filter.h"
#include "../../filter_maker.h"
#include "../../base_filter.h"
#include "../../../utils/utils.h"

#include <memory>

namespace image_processor::filters {

std::unique_ptr<BaseFilter> CreateEdgeDetectionFilterFromCmdArgs(const FilterDescriptor& fd) {

    static const int EDGE_DETECTION_FILTER_PARAMS_AMOUNT = 1;
    static const int THRESHOLD_INDEX = 0;

    if (fd.GetFilterParamsCount() != EDGE_DETECTION_FILTER_PARAMS_AMOUNT) {
        return nullptr;
    }

    auto& first_param = fd.filter_params[THRESHOLD_INDEX];

    if (!utils::IsFloatString(first_param)) {
        return nullptr;
    }

    float threshold = std::stof(first_param);

    return std::make_unique<EdgeDetectionFilter>(threshold);
}

}  // namespace image_processor::filters
