#include "filters_creator_factory.h"
#include "../clparser/clparser.h"
#include "../filters/filters.h"
#include "../filter_pipeline/filter_pipeline.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace image_processor {

template <typename T>
using CreationResult = std::pair<std::unique_ptr<T>, FiltersCreatorFactory::ErrorCode>;

CreationResult<filters::BaseFilter> FiltersCreatorFactory::CreateFilter(const FilterDescriptor& fd) const {
    auto it = filter_creator_map_.find(fd.filter_name);

    if (it == filter_creator_map_.end()) {
        return {nullptr, ErrorCode::FILTER_NOT_FOUND};
    }

    FilterCreatorFuncPtr filter_creator = it->second;

    auto filter = filter_creator(fd);

    if (!filter) {
        return {nullptr, ErrorCode::FILTER_ARGUMENT_ERROR};
    }

    return {std::move(filter), ErrorCode::OK};
}

CreationResult<FilterPipeline> FiltersCreatorFactory::CreatePipeline(
    const std::vector<FilterDescriptor>& filter_descriptors) const {
    std::unique_ptr<FilterPipeline> pipeline(new FilterPipeline());
    for (const auto& filter_descriptor : filter_descriptors) {

        auto [Filter, Error] = CreateFilter(filter_descriptor);

        if (Error != ErrorCode::OK) {
            return {nullptr, Error};
        }

        pipeline->AddFilter(std::move(Filter));
    }

    return {std::move(pipeline), ErrorCode::OK};
}

void FiltersCreatorFactory::RegisterFilterCreator(const std::string& filter_name, FilterCreatorFuncPtr filter_creator) {
    filter_creator_map_.insert({filter_name, filter_creator});
}

}  // namespace image_processor
