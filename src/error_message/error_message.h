#pragma once

#include <string>

namespace error_message {
std::string InvalidArgCountMessage();
std::string InvalidFilePathMessage();
std::string InvalidFilterNameMessage();
std::string InvalidFilterArgumentsMessage();
std::string UnsupportedFormatMessage();
std::string Usage();
std::string UndefinedMessage();
}  // namespace error_message