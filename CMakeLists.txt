cmake_minimum_required(VERSION 3.1 FATAL_ERROR)


project(image_filter)

find_package(OpenCV REQUIRED)

include_directories(
  include
  ${OpenCV_INCLUDE_DIR}
)

add_executable(image_filter
  src/image_filter_main.cpp
  src/image_filter.cpp
)


target_link_libraries(image_filter
  ${OpenCV_LIBS}
)


