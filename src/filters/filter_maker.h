#pragma once

#include "base_filter.h"
#include "../clparser/clparser.h"

#include <memory>

namespace image_processor::filters {

std::unique_ptr<BaseFilter> CreateCropFilterFromCmdArgs(const FilterDescriptor& fd);
std::unique_ptr<BaseFilter> CreateNegativeFilterFromCmdArgs(const FilterDescriptor& fd);
std::unique_ptr<BaseFilter> CreateGrayscaleFilterFromCmdArgs(const FilterDescriptor& fd);
std::unique_ptr<BaseFilter> CreateGaussianBlurFilterFromCmdArgs(const FilterDescriptor& fd);
std::unique_ptr<BaseFilter> CreateEdgeDetectionFilterFromCmdArgs(const FilterDescriptor& fd);
std::unique_ptr<BaseFilter> CreateSharpFilterFromCmdArgs(const FilterDescriptor& fd);
std::unique_ptr<BaseFilter> CreateGlassDistortionFilterFromCmdArgs(const FilterDescriptor& fd);
}  // namespace image_processor::filters