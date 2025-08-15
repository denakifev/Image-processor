#pragma once

#include "../clparser/clparser.h"
#include "../filters/filters.h"
#include "../filter_pipeline/filter_pipeline.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace image_processor {

class FiltersCreatorFactory {
public:
    enum class ErrorCode { OK = 0, FILTER_NOT_FOUND = 1, FILTER_ARGUMENT_ERROR = 2 };

    using FilterCreatorFuncPtr = std::unique_ptr<filters::BaseFilter> (*)(const FilterDescriptor& fd);
    using FilterName2CreatorMap = std::unordered_map<std::string, FilterCreatorFuncPtr>;

    template <typename T>
    using CreationResult = std::pair<std::unique_ptr<T>, ErrorCode>;

    void RegisterFilterCreator(const std::string& filter_name, FilterCreatorFuncPtr filter_creator);
    CreationResult<FilterPipeline> CreatePipeline(const std::vector<FilterDescriptor>& filter_descriptors) const;

protected:
    CreationResult<filters::BaseFilter> CreateFilter(const FilterDescriptor& fd) const;
    FilterName2CreatorMap filter_creator_map_;
};

}  // namespace image_processor
