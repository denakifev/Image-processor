#include <catch.hpp>
#include <cstring>

#include "../src/clparser/clparser.h"

using namespace image_processor;

TEST_CASE("Invalid args amount") {
    const char* test_case_1[] = {"./image_processor"};
    const char* test_case_2[] = {"./image_processor some_arg1"};
    std::vector<std::pair<int, char**> > test_cases = {{1, const_cast<char**>(test_case_1)},
                                                       {2, const_cast<char**>(test_case_2)}};

    std::vector<CLParser::ErrorCode> test_results = {
        CLParser::ErrorCode::ZERO_ARGUMENT_AMOUNT,
        CLParser::ErrorCode::INVALID_ARGUMENTS_AMOUNT,
    };

    for (size_t i = 0; i < 2; ++i) {
        CLParser parser;
        REQUIRE(parser.Parse(test_cases[i].first, test_cases[i].second) == test_results[i]);
    }
}

TEST_CASE("no flags") {
    const char* test_case_args[] = {"./image_processor", "some_arg1", "some_arg2"};

    std::pair<int, char**> test_case = {3, const_cast<char**>(test_case_args)};

    CLParser parser;
    REQUIRE(parser.Parse(test_case.first, test_case.second) == CLParser::ErrorCode::OK);
    REQUIRE(strcmp(parser.GetInputFilePath(), "some_arg1") == 0);
    REQUIRE(strcmp(parser.GetOutputFilePath(), "some_arg2") == 0);
    REQUIRE(parser.GetFilterDescriptors().size() == 0);
}

TEST_CASE("flags") {
    const char* test_case_1[] = {"./image_processor", "some_arg1", "-some_flag", "arg1", "arg2"};
    const char* test_case_2[] = {"./image_processor", "-v", "-c", "-k"};
    const char* test_case_3[] = {"./image_processor", "some_arg", "some_arg", "-f", "arg", "-v", "arg", "-c", "arg"};
    const char* test_case_4[] = {
        "./image_processor", "input.bmp", "/tmp/output.bmp", "-crop", "800", "600", "-gs", "-blur", "0.5"};

    std::vector<std::pair<int, char**> > test_cases = {{5, const_cast<char**>(test_case_1)},
                                                       {4, const_cast<char**>(test_case_2)},
                                                       {9, const_cast<char**>(test_case_3)},
                                                       {9, const_cast<char**>(test_case_4)}};

    std::vector<std::vector<FilterDescriptor> > expected_filters = {
        {{"arg1", {}}, {"arg2", {}}},
        {{"k", {}}},
        {{"f", {"arg"}}, {"v", {"arg"}}, {"c", {"arg"}}},
        {{"crop", {"800", "600"}}, {"gs", {}}, {"blur", {"0.5"}}}};

    for (size_t i = 0; i < test_cases.size(); ++i) {
        CLParser parser;
        REQUIRE(parser.Parse(test_cases[i].first, test_cases[i].second) == CLParser::ErrorCode::OK);
        REQUIRE(expected_filters[i].size() == parser.GetFilterDescriptors().size());
        for (size_t j = 0; j < expected_filters[i].size(); ++j) {
            REQUIRE(expected_filters[i][j].filter_name == parser.GetFilterDescriptors()[j].filter_name);
            REQUIRE(expected_filters[i][j].filter_params.size() ==
                    parser.GetFilterDescriptors()[j].filter_params.size());
            for (size_t k = 0; k < expected_filters[i][j].filter_params.size(); ++k) {
                REQUIRE(expected_filters[i][j].filter_params[k] == parser.GetFilterDescriptors()[j].filter_params[k]);
            }
        }
    }
}