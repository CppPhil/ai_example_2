cmake_minimum_required (VERSION 3.8)

set(APP_NAME ai_example_app)

set(
  APP_HEADERS
  idx_file.hpp "throw_with_source_info.hpp" "file_paths.hpp" "integer_interval_as_string_vector.hpp" "extract_grayscale_images.hpp" "dimension_constants.hpp" "extract_labels.hpp" "neural_network_constants.hpp" "neural_network.hpp" "image_size_from.hpp" "image_count.hpp" "extract_image.hpp" "as_double_vector.hpp" "io_constants.hpp" "closest_to_one.hpp" "gui_constants.hpp" "point.hpp" "size.hpp" "table.hpp" "collect_images.hpp" "invert_grayscale_image.hpp")

set(
  APP_SOURCES
  main.cpp
  idx_file.cpp "integer_interval_as_string_vector.cpp" "extract_grayscale_images.cpp" "extract_labels.cpp" "neural_network.cpp" "image_size_from.cpp" "image_count.cpp" "extract_image.cpp" "as_double_vector.cpp" "closest_to_one.cpp" "gui_constants.cpp" "table.cpp" "invert_grayscale_image.cpp")

add_executable(${APP_NAME} ${APP_HEADERS} ${APP_SOURCES} "collect_images.cpp")

target_include_directories(
  ${APP_NAME}
  PRIVATE
  ${ai_example_project_SOURCE_DIR}/external/fltk
  ${ai_example_project_SOURCE_DIR}/out/build/x64-Release/external/fltk
  ${ai_example_project_SOURCE_DIR}/external/genann)

if(WIN32)
  target_link_libraries(
    ${APP_NAME}
    PRIVATE
    Gdiplus.lib)
endif()

target_link_libraries(
  ${APP_NAME}
  PRIVATE
  fltk
  fltk_forms
  fltk_images
  CppPhil::philslib
  genann
  tl::expected
  fmt::fmt)
