#include "../src/filters/filters.h"
#include "../src/filters/filter_maker.h"
#include "../src/clparser/clparser.h"

#include <catch.hpp>
#include <vector>
#include <string>

using namespace image_processor;
using namespace image_processor::filters;

TEST_CASE("test_negative_filter_maker") {
    std::vector<FilterDescriptor> test_cases = {
        {"-neg", {}},
        {"-neg", {"arg"}},
        {"-neg", {"arg1", "arg2"}},
    };

    std::vector<bool> expected_results = {false, true, true};

    for (int i = 0; i < test_cases.size(); ++i) {
        auto test_case = test_cases[i];
        auto filter = CreateNegativeFilterFromCmdArgs(test_case);
        REQUIRE((filter == nullptr) == expected_results[i]);
    }
}

TEST_CASE("test_blur_filter_maker") {
    std::vector<FilterDescriptor> test_cases = {
        {"-blur", {}},       {"-blur", {"arg"}},          {"-blur", {"arg1", "arg2"}},
        {"-blur", {"0.75"}}, {"-blur", {"0.75", "0.75"}}, {"-blur", {"7"}},
        {"-blur", {"-7"}}};

    std::vector<bool> expected_results = {true, true, true, false, true, false, true};

    for (int i = 0; i < test_cases.size(); ++i) {
        auto test_case = test_cases[i];
        auto filter = CreateGaussianBlurFilterFromCmdArgs(test_case);
        REQUIRE((filter == nullptr) == expected_results[i]);
    }
}

TEST_CASE("test_crop_filter_maker") {
    std::vector<FilterDescriptor> test_cases = {
        {"-crop", {}},           {"-crop", {"arg"}},         {"-crop", {"arg1", "arg2"}}, {"-crop", {"0", "0"}},
        {"-crop", {"10", "10"}}, {"-crop", {"0", "0", "0"}}, {"-crop", {"10.5", "10.5"}}};

    std::vector<bool> expected_results = {true, true, true, false, false, true, true};

    for (int i = 0; i < test_cases.size(); ++i) {
        auto test_case = test_cases[i];
        auto filter = CreateCropFilterFromCmdArgs(test_case);
        REQUIRE((filter == nullptr) == expected_results[i]);
    }
}

TEST_CASE("test_grayscale_filter_maker") {
    std::vector<FilterDescriptor> test_cases = {
        {"-gs", {}},
        {"-gs", {"arg"}},
        {"-gs", {"arg1", "arg2"}},
    };

    std::vector<bool> expected_results = {false, true, true};

    for (int i = 0; i < test_cases.size(); ++i) {
        auto test_case = test_cases[i];
        auto filter = CreateGrayscaleFilterFromCmdArgs(test_case);
        REQUIRE((filter == nullptr) == expected_results[i]);
    }
}

TEST_CASE("test_sharp_filter_maker") {
    std::vector<FilterDescriptor> test_cases = {
        {"-sharp", {}},
        {"-sharp", {"arg"}},
        {"-sharp", {"arg1", "arg2"}},
    };

    std::vector<bool> expected_results = {false, true, true};

    for (int i = 0; i < test_cases.size(); ++i) {
        auto test_case = test_cases[i];
        auto filter = CreateSharpFilterFromCmdArgs(test_case);
        REQUIRE((filter == nullptr) == expected_results[i]);
    }
}

TEST_CASE("test_edge_detection_filter_maker") {
    std::vector<FilterDescriptor> test_cases = {
        {"-blur", {}},       {"-blur", {"arg"}},          {"-blur", {"arg1", "arg2"}},
        {"-blur", {"0.75"}}, {"-blur", {"0.75", "0.75"}}, {"-blur", {"7"}},
        {"-blur", {"-7"}}};

    std::vector<bool> expected_results = {true, true, true, false, true, false, true};

    for (int i = 0; i < test_cases.size(); ++i) {
        auto test_case = test_cases[i];
        auto filter = CreateEdgeDetectionFilterFromCmdArgs(test_case);
        REQUIRE((filter == nullptr) == expected_results[i]);
    }
}