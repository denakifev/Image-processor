include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src)
set(TEST_DATA_DIR ${CMAKE_BINARY_DIR}/test_data)
set(IMAGE_PROCESSOR_BIN ${CMAKE_BINARY_DIR}/image_processor)

if(WIN32)
  set(IMAGE_PROCESSOR_BIN ${IMAGE_PROCESSOR_BIN}.exe)
endif()

file(GLOB TEST_DATA_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test_data/*")
file(COPY ${TEST_DATA_FILES} DESTINATION ${TEST_DATA_DIR})

add_compile_definitions(TEST_DATA_DIR="${TEST_DATA_DIR}")

add_catch(test_parser test_parser.cpp ${SRC_DIR}/clparser/clparser.cpp ${SRC_DIR}/utils/utils.cpp)
add_catch(test_image test_image.cpp ${SRC_DIR}/image/image.cpp ${SRC_DIR}/utils/utils.cpp)
add_catch(test_crop_filter test_crop_filter.cpp ${SRC_DIR}/image/image.cpp ${SRC_DIR}/utils/utils.cpp)
add_catch(test_grayscale_filter test_grayscale_filter.cpp ${SRC_DIR}/image/image.cpp ${SRC_DIR}/utils/utils.cpp)
add_catch(test_negative_filter test_negative_filter.cpp ${SRC_DIR}/image/image.cpp ${SRC_DIR}/utils/utils.cpp)
add_catch(test_sharp_filter test_sharp_filter.cpp ${SRC_DIR}/image/image.cpp ${SRC_DIR}/utils/utils.cpp)
add_catch(test_edge_detection_filter test_edge_detection_filter.cpp ${SRC_DIR}/image/image.cpp ${SRC_DIR}/utils/utils.cpp)
add_catch(test_blur_filter test_blur_filter.cpp ${SRC_DIR}/image/image.cpp ${SRC_DIR}/utils/utils.cpp)
add_catch(test_glass_distortion_filter test_glass_distortion_filter.cpp ${SRC_DIR}/image/image.cpp ${SRC_DIR}/utils/utils.cpp)
add_catch(test_filter_makers test_filter_makers.cpp ${SRC_DIR}/clparser/clparser.cpp ${SRC_DIR}/utils/utils.cpp ${SRC_DIR}/image/image.cpp)

target_link_libraries(test_crop_filter filters)
target_link_libraries(test_grayscale_filter filters)
target_link_libraries(test_negative_filter filters)
target_link_libraries(test_sharp_filter filters)
target_link_libraries(test_edge_detection_filter filters)
target_link_libraries(test_blur_filter filters)
target_link_libraries(test_glass_distortion_filter filters)
target_link_libraries(test_filter_makers filters)

add_custom_target(run_py3_tests
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_image_processor.py ${IMAGE_PROCESSOR_BIN}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  DEPENDS setup_py3_venv
  COMMENT "Running Python tests inside virtualenv..."
)


add_custom_target(run_cpp_tests
    COMMAND test_parser
    COMMAND test_image
    COMMAND test_crop_filter
    COMMAND test_grayscale_filter
    COMMAND test_negative_filter
    COMMAND test_sharp_filter
    COMMAND test_edge_detection_filter
    COMMAND test_filter_makers
    COMMAND test_blur_filter
    COMMAND test_glass_distortion_filter
    DEPENDS test_parser test_image test_crop_filter test_grayscale_filter test_negative_filter test_sharp_filter test_edge_detection_filter test_blur_filter test_filter_makers test_glass_distortion_filter
)

add_custom_target(run_all_tests
    COMMAND make run_cpp_tests
    COMMAND make run_py3_tests
)