#include "utils.h"

#include <cstdint>
#include <filesystem>
#include <regex>
#include <string>

bool utils::IsFloatString(const std::string& str) {
    const std::regex pattern(R"(^\d+(\.\d+)?$)");
    return std::regex_match(str, pattern);
}

bool utils::IsIntegerString(const std::string& str) {
    const std::regex pattern(R"(^\d+$)");
    return std::regex_match(str, pattern);
}

bool utils::IsFlag(const char* arg) {
    return arg[0] == '-';
}

int32_t utils::CalculatePadding(int32_t width) {
    return (4 - (width * 3) % 4) % 4;
}

bool utils::IsCorrectFilePath(const std::string& path) {
    return std::filesystem::exists(path);
}