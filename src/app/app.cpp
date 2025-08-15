#include "app.h"

#include "../clparser/clparser.h"
#include "../error_message/error_message.h"
#include "../filters/filters.h"
#include "../filters/filter_maker.h"
#include "../filter_pipeline/filter_pipeline.h"
#include "../filters_creator_factory/filters_creator_factory.h"
#include "../image/image.h"
#include "../utils/utils.h"

#include <iostream>
#include <stdexcept>

namespace image_processor {

App::App(int args, char** argv) : factory_(), parser_(), argc_(args), argv_(argv) {
    InitFilters();
}

void App::InitFilters() {
    factory_.RegisterFilterCreator("crop", filters::CreateCropFilterFromCmdArgs);
    factory_.RegisterFilterCreator("gs", filters::CreateGrayscaleFilterFromCmdArgs);
    factory_.RegisterFilterCreator("edge", filters::CreateEdgeDetectionFilterFromCmdArgs);
    factory_.RegisterFilterCreator("blur", filters::CreateGaussianBlurFilterFromCmdArgs);
    factory_.RegisterFilterCreator("neg", filters::CreateNegativeFilterFromCmdArgs);
    factory_.RegisterFilterCreator("sharp", filters::CreateSharpFilterFromCmdArgs);
    factory_.RegisterFilterCreator("glass", filters::CreateGlassDistortionFilterFromCmdArgs);
}

void App::Run() {
    CLParser::ErrorCode parse_status = parser_.Parse(argc_, argv_);

    if (parse_status == CLParser::ErrorCode::ZERO_ARGUMENT_AMOUNT) {
        std::cerr << error_message::Usage() << std::endl;
        return;
    }

    if (parse_status == CLParser::ErrorCode::INVALID_ARGUMENTS_AMOUNT) {
        std::cerr << error_message::InvalidArgCountMessage() << std::endl;
        return;
    }

    if (!utils::IsCorrectFilePath(parser_.GetInputFilePath()) ||
        !utils::IsCorrectFilePath(parser_.GetOutputFilePath())) {
        std::cerr << error_message::InvalidFilePathMessage() << std::endl;
        return;
    }

    auto [filter_pipeline, error_code] = factory_.CreatePipeline(parser_.GetFilterDescriptors());

    if (error_code == FiltersCreatorFactory::ErrorCode::FILTER_NOT_FOUND) {
        std::cerr << error_message::InvalidFilterNameMessage() << std::endl;
        return;
    }

    if (error_code == FiltersCreatorFactory::ErrorCode::FILTER_ARGUMENT_ERROR) {
        std::cerr << error_message::InvalidFilterArgumentsMessage() << std::endl;
        return;
    }

    try {
        Image image(parser_.GetInputFilePath());
        filter_pipeline->Apply(image);
        image.Save(parser_.GetOutputFilePath());
    } catch (const std::runtime_error& e) {
        std::cerr << error_message::UnsupportedFormatMessage() << std::endl;
        return;
    }
}

}  // namespace image_processor