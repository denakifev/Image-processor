#include "error_message.h"

#include <string>

std::string error_message::UndefinedMessage() {
    return std::string("Error: Undefined error!\n");
}

std::string error_message::Usage() {
    return std::string(
        "Usage: ./image_processor {input_file_path} {output_file_path}"
        "[-{filter_name1} [arg1] [arg2] ...]"
        "[-{filter_name2} [arg1] [arg2] ...] ...\n"
        "Currently available filters: crop, grayscale, edge detection, gaussian blur, negative, sharp, glass distortion\n"
        "Filters can be applied in any order\n"
        "Crop filter signature: [-crop width height]\n"
        "Grayscale filter signature: [-gs]\n"
        "Edge detection filter signature: [-edge threshold]\n"
        "Gaussian blur filter signature: [-blur sigma]\n"
        "Negative filter signature: [-neg]\n"
        "Sharp filter signature: [-sharp]\n"
        "Glass Distortion filter signature: [-glass strength]\n"
    );
}

std::string error_message::InvalidArgCountMessage() {
    return std::string("Error: Invalid arguments amount were passed!\n" + Usage());
}

std::string error_message::InvalidFilePathMessage() {
    return std::string("Error: Invalid file path!\n" + Usage());
}

std::string error_message::InvalidFilterNameMessage() {
    return std::string("Error: Unknown filter name were provided!\n" + Usage());
}

std::string error_message::InvalidFilterArgumentsMessage() {
    return std::string("Error: Invalid filter arguments were provided!\n" + Usage());
}

std::string error_message::UnsupportedFormatMessage() {
    return std::string(
        "Error: Unsupported image format!\n"
        "Currently available format is 24-bit BMP without compression and without a color table \n");
}