#pragma once

#include <string>
#include <vector>

namespace image_processor {

struct FilterDescriptor {
    std::string filter_name;
    std::vector<std::string> filter_params;
    size_t GetFilterParamsCount() const;
    FilterDescriptor(std::string filter_name, std::vector<std::string> filter_params);
};

class CLParser {
public:
    using FilterDescriptors = std::vector<FilterDescriptor>;

    enum class ErrorCode { OK = 0, INVALID_ARGUMENTS_AMOUNT = 1, ZERO_ARGUMENT_AMOUNT = 2 };

    CLParser();
    ErrorCode Parse(int argc, char** argv);

    const char* GetInputFilePath() const;
    const char* GetOutputFilePath() const;
    const FilterDescriptors& GetFilterDescriptors() const;

protected:
    constexpr static int MinArgsAmount = 3;
    constexpr static int InputFilePosition = 1;
    constexpr static int OutputFilePosition = 2;
    FilterDescriptors filter_descriptors_;
    const char* input_file_path_;
    const char* output_file_path_;
};

}  // namespace image_processor