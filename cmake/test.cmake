function(patch_include_directories TARGET)
  target_include_directories(${TARGET}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endfunction()

function(add_hse_executable NAME)
  add_executable(${NAME}
    ${ARGN})
  patch_include_directories(${NAME})
endfunction()

function(add_catch TARGET)
  add_hse_executable(${TARGET}
    ${ARGN})

  target_link_libraries(${TARGET}
    contrib_catch_main)
endfunction()
