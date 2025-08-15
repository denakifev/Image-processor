#include "clparser.h"
#include "../utils/utils.h"

#include <string>
#include <vector>

namespace image_processor {

size_t FilterDescriptor::GetFilterParamsCount() const {
    return filter_params.size();
}

FilterDescriptor::FilterDescriptor(std::string filter_name, std::vector<std::string> filter_params)
    : filter_name(filter_name), filter_params(filter_params) {
}

CLParser::CLParser() : input_file_path_(nullptr), output_file_path_(nullptr) {
}

CLParser::ErrorCode CLParser::Parse(int argc, char** argv) {

    if (argc == 1) {
        return ErrorCode::ZERO_ARGUMENT_AMOUNT;
    }

    if (argc < MinArgsAmount) {
        return ErrorCode::INVALID_ARGUMENTS_AMOUNT;
    }

    input_file_path_ = argv[InputFilePosition];
    output_file_path_ = argv[OutputFilePosition];

    int current = MinArgsAmount;
    while (current < argc) {
        const char* filter_name = argv[current++];
        if (!utils::IsFlag(filter_name)) {
            filter_descriptors_.emplace_back(filter_name, std::vector<std::string>());
        } else {
            std::vector<std::string> filter_args;
            while (current < argc && !utils::IsFlag(argv[current])) {
                filter_args.emplace_back(argv[current]);
                ++current;
            }
            filter_descriptors_.emplace_back(++filter_name, std::move(filter_args));
        }
    }

    return ErrorCode::OK;
}

const char* CLParser::GetInputFilePath() const {
    return input_file_path_;
}

const char* CLParser::GetOutputFilePath() const {
    return output_file_path_;
}

const CLParser::FilterDescriptors& CLParser::GetFilterDescriptors() const {
    return filter_descriptors_;
}

}  // namespace image_processor
