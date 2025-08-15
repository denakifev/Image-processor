#pragma once

#include <cstdint>
#include <string>

namespace utils {
int32_t CalculatePadding(int32_t width);
bool IsIntegerString(const std::string& str);
bool IsFloatString(const std::string& str);
bool IsFlag(const char* arg);
bool IsCorrectFilePath(const std::string& path);
}  // namespace utils