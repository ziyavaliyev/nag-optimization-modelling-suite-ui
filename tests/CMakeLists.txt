# info@stce.rwth-aachen.de
# C++ UI design for NAG Optimization Modelling Suite
# Group 6: Tran, Man Khang; Feldman, Maksim; Valiyev, Ziya; Korkin, Konstantin; Huang, Yifei
# Superviser: Lotz, Johannes

## Helper macro used below: get all directories in dir.
macro(get_subdirs dir result)
  file(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${dir} ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/*)
  set(dirlist "")
  foreach(child ${children})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/${child})
      list(APPEND dirlist ${child})
    endif()
  endforeach()
  set(${result} ${dirlist})
endmacro()

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

get_subdirs(. dirs)
add_custom_target(tests)
foreach(dir ${dirs})
  file(GLOB files ${dir}/*.cpp)
  add_executable(tests.${dir} ${files})
  target_compile_definitions(tests.${dir}
    PRIVATE DCO_DISABLE_AUTO_WARNING DCO_DISABLE_AVX2_WARNING)
  target_link_libraries(tests.${dir} PRIVATE GTest::GTest code)
  add_test(tests.${dir} tests.${dir})
endforeach()
