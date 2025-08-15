cmake_minimum_required(VERSION 3.8)
project(image_processor)

set(CMAKE_MODULE_PATH              "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

include(cmake/build_flags.cmake)
include(cmake/find_catch.cmake)
include(cmake/test.cmake)
include(cmake/conf_py3test.cmake)

find_package(Python3 COMPONENTS Interpreter REQUIRED)

add_executable(
    image_processor
    src/main.cpp
    src/app/app.cpp
    src/clparser/clparser.cpp
    src/filters_creator_factory/filters_creator_factory.cpp
    src/filter_pipeline/filter_pipeline.cpp
    src/error_message/error_message.cpp
    src/image/image.cpp
    src/utils/utils.cpp
)

add_subdirectory(src/filters)
add_subdirectory(tests)

target_link_libraries(image_processor filters)