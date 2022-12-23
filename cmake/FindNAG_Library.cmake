# info@stce.rwth-aachen.de
# C++ UI design for NAG Optimization Modelling Suite
# Group 6: Tran, Man Khang; Feldman, Maksim; Valiyev, Ziya; Korkin, Konstantin; Huang, Yifei
# Superviser: Lotz, Johannes

cmake_minimum_required(VERSION 2.9)

if (NOT(NAG_Library_suppress))
  message(WARNING "FindNAG_Library: Module in alpha state. Only tested for MK27.3 (following product codes: NLL6I273BL, NLW6I273EL). [Suppress this warning with -DNAG_Library_suppress=ON]")
endif()

if (WIN32)
  set(NAG_Library_DIR "$ENV{NAG_NLW6I273EL}" CACHE STRING "Set root directory to NAG Library.")
else()
  set(NAG_Library_DIR "$ENV{HOME}/NAG/nll6i273bl" CACHE STRING "Set root directory to NAG Library.")
endif()
message(STATUS "NAG_Library_DIR set to '${NAG_Library_DIR}'.")

if (NOT(WIN32))
  if (NOT(NAG_Library_INTEGER_SIZE))
    set(NAG_Library_INTEGER_SIZE "64" CACHE STRING "Choose the integer size to use.")
    set_property(CACHE NAG_Library_INTEGER_SIZE PROPERTY STRINGS "32" "64")
    message(STATUS "NAG_Library_INTEGER_SIZE set to '${NAG_Library_INTEGER_SIZE}'. Possible values: '32', '64'.")
  endif()
else()
  if (NOT(NAG_Library_USE_DYNAMIC_RT))
    set(NAG_Library_USE_DYNAMIC_RT "ON" CACHE BOOL "Choose whether to use dynamic runtime library (MD).")
  endif()
    message(STATUS "NAG_Library_USE_DYNAMIC_RT set to '${NAG_Library_USE_DYNAMIC_RT}'. Possible values: 'ON', 'OFF'.")
  if (NAG_Library_USE_DYNAMIC_RT)
    set(_mdmt_postfix "MD")
  else()
    set(_mdmt_postfix "MT")
  endif()
endif()

if (NOT(NAG_Library_LINEAR_ALGEBRA_LIBRARY))
  set(NAG_Library_LINEAR_ALGEBRA_LIBRARY "nag" CACHE STRING "Choose which underlying linear algebra library to use.")
  set_property(CACHE NAG_Library_LINEAR_ALGEBRA_LIBRARY PROPERTY STRINGS "nag" "vendor")
  message(STATUS "NAG_Library_LINEAR_ALGEBRA_LIBRARY set to '${NAG_Library_LINEAR_ALGEBRA_LIBRARY}'. Possible values: 'nag', 'vendor'")
endif()

if (NOT(NAG_Library_USE_DYNAMIC))
  set(NAG_Library_USE_DYNAMIC ON CACHE BOOL "Choose whether to use dynamic library.")
  message(STATUS "NAG_Library_USE_DYNAMIC set to '${NAG_Library_USE_DYNAMIC}'. Possible values: 'ON', 'OFF'.")
endif()

get_filename_component(NAG_Library_DIR "${NAG_Library_DIR}" ABSOLUTE)

if (WIN32)
  set(_prefix "")
else()
  if (NAG_Library_INTEGER_SIZE STREQUAL "64")
    set(_prefix "ilp64")
  elseif(NAG_Library_INTEGER_SIZE STREQUAL "32")
    set(_prefix "lp64")
  else()
    message(FATAL_ERROR "NAG_Library_INTEGER_SIZE set to an invalid value: '${NAG_Library_INTEGER_SIZE}'. Set to '32' or '64'.")
  endif()
endif()

if (NAG_Library_LINEAR_ALGEBRA_LIBRARY STREQUAL "nag")
  set(_la_lib_fix "nag")
elseif(NAG_Library_LINEAR_ALGEBRA_LIBRARY STREQUAL "vendor")
  set(_la_lib_fix "mkl")
else()
  message(FATAL_ERROR "NAG_Library_LINEAR_ALGEBRA_LIBRARY set to an invalid value: '${NAG_Library_LINEAR_ALGEBRA_LIBRARY}'. Set to 'nag' or 'vendor'.")
endif()

find_path(NAG_Library_INCLUDE_DIR nag.h
  HINTS
  ${NAG_Library_DIR}/${_prefix}/include)

if (NOT(NAG_Library_INCLUDE_DIR))
  message(FATAL_ERROR "nag.h not found! Currently only poor automatic installation folder detection. Set NAG_Library_DIR manually.")
endif()

find_path(NAG_Library_LIBRARY_DIR NAMES libnag_${_la_lib_fix}.a nag_${_la_lib_fix}_${_mdmt_postfix}.lib
  HINTS
  ${NAG_Library_DIR}/${_prefix}/lib)

find_path(NAG_Library_BINARY_DIR NAMES libnag_${_la_lib_fix}.so NLW6I273E_${_la_lib_fix}.dll
  HINTS
  ${NAG_Library_DIR}/${_prefix}/lib
  ${NAG_Library_DIR}/${_prefix}/bin)

if (NAG_Library_USE_DYNAMIC)
  add_library(NAG::Library SHARED IMPORTED GLOBAL)
  find_library(NAG_Library_LIBRARY NAMES libnag_${_la_lib_fix}.so NLW6I273E_${_la_lib_fix}.lib HINTS ${NAG_Library_LIBRARY_DIR})
  if (WIN32)
    set_target_properties(NAG::Library PROPERTIES IMPORTED_SONAME "${NAG_Library_BINARY_DIR}/NLW6I273E_${_la_lib_fix}.dll")
    set_target_properties(NAG::Library PROPERTIES IMPORTED_SONAME_RELEASE "${NAG_Library_BINARY_DIR}/NLW6I273E_${_la_lib_fix}.dll")
    set_target_properties(NAG::Library PROPERTIES IMPORTED_IMPLIB "${NAG_Library_LIBRARY}")
    set_target_properties(NAG::Library PROPERTIES IMPORTED_LOCATION "${NAG_Library_BINARY_DIR}/NLW6I273E_${_la_lib_fix}.dll")
    set_target_properties(NAG::Library PROPERTIES LINK_LIBRARIES "${NAG_Library_LIBRARY}")
  else()
    set_target_properties(NAG::Library PROPERTIES IMPORTED_SONAME "${NAG_Library_LIBRARY}")
    set_target_properties(NAG::Library PROPERTIES IMPORTED_SONAME_RELEASE "${NAG_Library_LIBRARY}")

    set(_rtl_directories "${NAG_Library_DIR}/rtl/lib/intel64;${NAG_Library_DIR}/mkl/lib/intel64")
    set_target_properties(NAG::Library    PROPERTIES INTERFACE_LINK_DIRECTORIES "${_rtl_directories}")
    set_target_properties(NAG::Library    PROPERTIES IMPORTED_LOCATION "${NAG_Library_LIBRARY}")
    set_target_properties(NAG::Library    PROPERTIES INTERFACE_LINK_LIBRARIES "${NAG_Library_LIBRARY}")
  endif()
else()
  add_library(NAG::Library STATIC IMPORTED GLOBAL)
  find_library(NAG_Library_LIBRARY NAMES libnag_${_la_lib_fix}.a  nag_${_la_lib_fix}_${_mdmt_postfix}.lib HINTS ${NAG_Library_LIBRARY_DIR})
  set_target_properties(NAG::Library PROPERTIES IMPORTED_LOCATION "${NAG_Library_LIBRARY}")
  set_target_properties(NAG::Library PROPERTIES LINK_LIBRARIES "${NAG_Library_LIBRARY}")
endif()

if (NAG_Library_USE_DYNAMIC)
  add_library(NAG::Library_AD SHARED IMPORTED GLOBAL)
  find_library(NAG_Library_AD_LIBRARY NAMES libnag_${_la_lib_fix}_ad.so NLW6I273E_${_la_lib_fix}_ad.lib HINTS ${NAG_Library_LIBRARY_DIR})
  if (WIN32)
    set_target_properties(NAG::Library_AD PROPERTIES IMPORTED_SONAME "${NAG_Library_AD_BINARY_DIR}/NLW6I273E_${_la_lib_fix}_ad.dll")
    set_target_properties(NAG::Library_AD PROPERTIES IMPORTED_SONAME_RELEASE "${NAG_Library_AD_BINARY_DIR}/NLW6I273E_${_la_lib_fix}_ad.dll")
    set_target_properties(NAG::Library_AD PROPERTIES IMPORTED_IMPLIB "${NAG_Library_AD_LIBRARY}")
    set_target_properties(NAG::Library_AD PROPERTIES IMPORTED_LOCATION "${NAG_Library_BINARY_DIR}/NLW6I273E_${_la_lib_fix}_ad.dll")
  else()
    set_target_properties(NAG::Library_AD PROPERTIES IMPORTED_SONAME "${NAG_Library_AD_LIBRARY}")
    set_target_properties(NAG::Library_AD PROPERTIES IMPORTED_SONAME_RELEASE "${NAG_Library_AD_LIBRARY}")
    set_target_properties(NAG::Library_AD PROPERTIES INTERFACE_LINK_DIRECTORIES "${_rtl_directory};${_rtl_directory_mkl}")
    set_target_properties(NAG::Library_AD PROPERTIES IMPORTED_LOCATION "${NAG_Library_AD_LIBRARY}")
  endif()
else()
  add_library(NAG::Library_AD STATIC IMPORTED GLOBAL)
  find_library(NAG_Library_AD_LIBRARY NAMES libnag_${_la_lib_fix}_ad.a  nag_${_la_lib_fix}_ad_${_mdmt_postfix}.lib HINTS ${NAG_Library_LIBRARY_DIR})
  set_target_properties(NAG::Library_AD PROPERTIES IMPORTED_LOCATION "${NAG_Library_AD_LIBRARY}")
endif()

if (NAG_Library_INCLUDE_DIR AND NAG_Library_LIBRARY_DIR)
  
  set_target_properties(NAG::Library PROPERTIES INCLUDE_DIRECTORIES "${NAG_Library_INCLUDE_DIR}")
  set_target_properties(NAG::Library PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${NAG_Library_INCLUDE_DIR}")
  
  set(NAG_Library_FOUND TRUE)
  set(NAG_Library_INCLUDE_DIRS ${NAG_Library_INCLUDE_DIR})
  set(NAG_Library_LIBRARIES ${NAG_Library_LIBRARY})
  set(NAG_Library_RUNTIME_LIBRARY_DIRS ${NAG_Library_BINARY_DIR})

  set_target_properties(NAG::Library_AD PROPERTIES INTERFACE_LINK_LIBRARIES "NAG::Library;NAG::dco_cpp")
else()

  set(NAG_Library_FOUND FALSE)

endif()

## This function tries to collect all potentially required runtime
## libraries. It copies the DLLs into 'dest_dir'. With that, a
## distribution of the executable onto another machine should be
## possible without having to install the NAG Library there.
function (NAG_Library_install_rtl dest_dir)
  if (NOT(NAG_Library_FOUND))
    message(FATAL_ERROR "NAG::Library: Trying to install the runtime libraries; but NAG_Library not found.") 
  endif()
  if (NOT(WIN32))
    message(FATAL_ERROR "NAG::Library: Installing the runtime libraries not supported yet under Linux.")   
  endif()
    file(GLOB runtime_deps "${NAG_Library_BINARY_DIR}/*.dll")
    file(COPY ${runtime_deps} DESTINATION ${dest_dir})
    file(GLOB runtime_deps "${NAG_Library_DIR}/rtl/bin/*.dll")
    file(COPY ${runtime_deps} DESTINATION ${dest_dir})
    file(GLOB runtime_deps "${NAG_Library_DIR}/mkl/bin/*.dll")
    file(COPY ${runtime_deps} DESTINATION ${dest_dir})
endfunction()
