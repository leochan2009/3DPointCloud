
cmake_minimum_required(VERSION 2.8)

PROJECT(PointSource)

get_filename_component(PARENT_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)
set(VTK_DIR "${PARENT_DIR}/Slicer-unixBuild/VTKv6-build")
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_library(plyReader vtkPLYReaderLocal.cpp)
add_library(PointCloud vtkPointSource.cxx)
add_executable(PointSource MACOSX_BUNDLE PointSource)

if(VTK_LIBRARIES)
  target_link_libraries(PointSource ${VTK_LIBRARIES} plyReader PointCloud)
else()
  target_link_libraries(PointSource vtkHybrid vtkWidgets plyReader PointCloud)
endif()
