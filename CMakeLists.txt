# info@stce.rwth-aachen.de
# C++ UI design for NAG Optimization Modelling Suite
# Group 6: Tran, Man Khang; Feldman, Maksim; Valiyev, Ziya; Korkin, Konstantin; Huang, Yifei
# Superviser: Lotz, Johannes

cmake_minimum_required(VERSION 3.16)
project(CodeTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(NAG_Library_suppress ON)
find_package(NAG_dco_cpp REQUIRED)
find_package(NAG_Library REQUIRED)
set(NAG_CPP_DIR ${CMAKE_SOURCE_DIR}/thirdParty/nag_cpp)


add_library(code INTERFACE)
target_include_directories(
  code
  INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${NAG_CPP_DIR}
  )
target_link_libraries(code INTERFACE NAG::dco_cpp NAG::Library)

enable_testing()
add_subdirectory(examples)
add_subdirectory(caseStudies)
add_subdirectory(tests)
