###  06062019
#__author__: Ming Song， LUH for Master thesis
#__function__: Extract 3d consistency

set(CMAKE_CXX_STANDARD 14)
cmake_minimum_required(VERSION 2.8)
project( 3d_consistency_graph )

find_package( OpenCV REQUIRED )

# message( ${OpenCV_VERSION} )

include_directories(
  include
)

add_executable( visualize_consistency
  src/visualize_consistency.cpp
  include/3d_consistency_graph/visualize_consistency.h
)

target_link_libraries(
  visualize_consistency ${OpenCV_LIBS}
)
