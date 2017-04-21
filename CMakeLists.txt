cmake_minimum_required(VERSION 3.0)

if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Release" CACHE STRING
       "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x600)
    add_definitions(-DUNICODE -D_UNICODE)
    add_definitions(/MP)
    if(NOT MSVC)
        message(FATAL_ERROR, "Only testing for vcpkg integration on Windows")
    endif(NOT MSVC)
endif(WIN32)

message(STATUS "Building for ${CMAKE_BUILD_TYPE}")

#
# xalan-c
#
find_path(XALANC_INCLUDE NAMES "xalanc/Include/PlatformDefinitions.hpp")
find_library(XALANC_LIBRARY_DEBUG NAMES Xalan-C_1D)
find_library(XALANC_LIBRARY_RELEASE NAMES Xalan-C_1)
if(NOT XALANC_INCLUDE)
    message(FATAL_ERROR "xalan-c include path not found")
else(NOT XALANC_INCLUDE)
    message(STATUS "Found xalan-c include path: ${XALANC_INCLUDE}")
endif()
# This is the suggested pattern for finding debug/release libraries in multi-config generators like VS
# https://cmake.org/Bug/view.php?id=13588&history=1
if(XALANC_LIBRARY_DEBUG AND XALANC_LIBRARY_RELEASE)
    set(XALANC_LIBRARY optimized ${XALANC_LIBRARY_RELEASE} debug ${XALANC_LIBRARY_DEBUG})
    message(STATUS "Found xalan-c library")
elseif(XALANC_LIBRARY_RELEASE)
    set(XALANC_LIBRARY ${XALANC_LIBRARY_RELEASE})
    message(STATUS "Found xalan-c release library: ${XALANC_LIBRARY}")
elseif(XALANC_LIBRARY_DEBUG)
    set(XALANC_LIBRARY ${XALANC_LIBRARY_DEBUG})
    message(STATUS "Found xalan-c debug library: ${XALANC_LIBRARY}")
else()
    message(FATAL_ERROR "xalan-c library not found")
endif()

#
# xerces-c
#
find_path(XERCESC_INCLUDE NAMES "xercesc/util/PlatformUtils.hpp")
find_library(XERCESC_LIBRARY_DEBUG NAMES xerces-c_3D)
find_library(XERCESC_LIBRARY_RELEASE NAMES xerces-c_3)
if(NOT XERCESC_INCLUDE)
    message(FATAL_ERROR "xerces-c include path not found")
else(NOT XERCESC_INCLUDE)
    message(STATUS "Found xerces-c include path: ${XERCESC_INCLUDE}")
endif()
# This is the suggested pattern for finding debug/release libraries in multi-config generators like VS
# https://cmake.org/Bug/view.php?id=13588&history=1
if(XERCESC_LIBRARY_DEBUG AND XERCESC_LIBRARY_RELEASE)
    set(XERCESC_LIBRARY optimized ${XERCESC_LIBRARY_RELEASE} debug ${XERCESC_LIBRARY_DEBUG})
    message(STATUS "Found xerces-c library")
elseif(XERCESC_LIBRARY_RELEASE)
    set(XERCESC_LIBRARY ${XERCESC_LIBRARY_RELEASE})
    message(STATUS "Found xerces-c release library: ${XERCESC_LIBRARY}")
elseif(XERCESC_LIBRARY_DEBUG)
    set(XERCESC_LIBRARY ${XERCESC_LIBRARY_DEBUG})
    message(STATUS "Found xerces-c debug library: ${XERCESC_LIBRARY}")
else()
    message(FATAL_ERROR "xerces-c library not found")
endif()

#
# libgd
#
find_path(GD_INCLUDE NAMES "gd.h")
find_library(GD_LIBRARY NAMES libgd)
if(NOT GD_INCLUDE)
    message(FATAL_ERROR "GD include path not found")
else(NOT GD_INCLUDE)
    message(STATUS "Found GD include path: ${GD_INCLUDE}")
endif()
if(NOT GD_LIBRARY)
    message(FATAL_ERROR "GD library not found")
else(NOT GD_LIBRARY)
    message(STATUS "Found GD library: ${GD_LIBRARY}")
endif()

#
# geos
#
find_path(GEOS_INCLUDE NAMES "geos/geos.h")
find_library(GEOS_LIBRARY NAMES geos)
if(NOT GEOS_INCLUDE)
    message(FATAL_ERROR "GEOS include path not found")
else(NOT GEOS_INCLUDE)
    message(STATUS "Found GEOS include path: ${GEOS_INCLUDE}")
endif()
if(NOT GEOS_LIBRARY)
    message(FATAL_ERROR "GEOS library not found")
else(NOT GEOS_LIBRARY)
    message(STATUS "Found GEOS library: ${GEOS_LIBRARY}")
endif()

add_subdirectory(xalan-c)
add_subdirectory(xerces-c)
add_subdirectory(libgd)
add_subdirectory(geos)