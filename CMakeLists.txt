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

if(TEST_STATIC)
    # Required for vcpkg static ports
    # https://blogs.msdn.microsoft.com/vcblog/2016/11/01/vcpkg-updates-static-linking-is-now-available/
    # http://stackoverflow.com/questions/14172856/cmake-compile-with-mt-instead-of-md
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif(TEST_STATIC)

message(STATUS "Building for ${CMAKE_BUILD_TYPE}")

if(NOT TEST_STATIC)
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

    #
    # gdal
    #
    find_path(GDAL_INCLUDE NAMES "gdal.h")
    find_library(GDAL_LIBRARY_DEBUG NAMES gdald)
    find_library(GDAL_LIBRARY_RELEASE NAMES gdal)
    if(NOT GDAL_INCLUDE)
        message(FATAL_ERROR "gdal include path not found")
    else(NOT GDAL_INCLUDE)
        message(STATUS "Found gdal include path: ${GDAL_INCLUDE}")
    endif()
    # This is the suggested pattern for finding debug/release libraries in multi-config generators like VS
    # https://cmake.org/Bug/view.php?id=13588&history=1
    if(GDAL_LIBRARY_DEBUG AND GDAL_LIBRARY_RELEASE)
        set(GDAL_LIBRARY optimized ${GDAL_LIBRARY_RELEASE} debug ${GDAL_LIBRARY_DEBUG})
        message(STATUS "Found gdal library")
    elseif(GDAL_LIBRARY_RELEASE)
        set(GDAL_LIBRARY ${GDAL_LIBRARY_RELEASE})
        message(STATUS "Found gdal release library: ${GDAL_LIBRARY}")
    elseif(GDAL_LIBRARY_DEBUG)
        set(GDAL_LIBRARY ${GDAL_LIBRARY_DEBUG})
        message(STATUS "Found gdal debug library: ${GDAL_LIBRARY}")
    else()
        message(FATAL_ERROR "gdal library not found")
    endif()
endif() # NOT TEST_STATIC

#
# cppunit
#
find_path(CPPUNIT_INCLUDE NAMES "cppunit/extensions/HelperMacros.h")
if(NOT TEST_STATIC)
    find_library(CPPUNIT_LIBRARY_DEBUG NAMES cppunitd_dll)
    find_library(CPPUNIT_LIBRARY_RELEASE NAMES cppunit_dll)
else(NOT TEST_STATIC)
    find_library(CPPUNIT_LIBRARY_DEBUG NAMES cppunitd)
    find_library(CPPUNIT_LIBRARY_RELEASE NAMES cppunit)
endif()
if(NOT CPPUNIT_INCLUDE)
    message(FATAL_ERROR "cppunit include path not found")
else(NOT CPPUNIT_INCLUDE)
    message(STATUS "Found cppunit include path: ${CPPUNIT_INCLUDE}")
endif()
# This is the suggested pattern for finding debug/release libraries in multi-config generators like VS
# https://cmake.org/Bug/view.php?id=13588&history=1
if(CPPUNIT_LIBRARY_DEBUG AND CPPUNIT_LIBRARY_RELEASE)
    set(CPPUNIT_LIBRARY optimized ${CPPUNIT_LIBRARY_RELEASE} debug ${CPPUNIT_LIBRARY_DEBUG})
    message(STATUS "Found cppunit library")
elseif(CPPUNIT_LIBRARY_RELEASE)
    set(CPPUNIT_LIBRARY ${CPPUNIT_LIBRARY_RELEASE})
    message(STATUS "Found cppunit release library: ${CPPUNIT_LIBRARY}")
elseif(CPPUNIT_LIBRARY_DEBUG)
    set(CPPUNIT_LIBRARY ${CPPUNIT_LIBRARY_DEBUG})
    message(STATUS "Found cppunit debug library: ${CPPUNIT_LIBRARY}")
else()
    message(FATAL_ERROR "cppunit library not found")
endif()

if(TEST_STATIC)
    #
    # zlib
    #
    find_package(ZLIB REQUIRED)
    if(NOT ZLIB_FOUND)
        message(FATAL_ERROR "zlib library not found")
    endif(NOT ZLIB_FOUND)

    #
    # bzip2
    #
    find_package(BZIP2 REQUIRED)
    if(NOT BZIP2_FOUND)
        message(FATAL_ERROR "bzip2 library not found")
    endif(NOT BZIP2_FOUND)

    #
    # libpng
    #
    find_package(PNG REQUIRED)
    if(NOT PNG_FOUND)
        message(FATAL_ERROR "png library not found")
    endif(NOT PNG_FOUND)

    #
    # libjpeg-turbo
    #
    find_package(JPEG REQUIRED)
    if(NOT JPEG_FOUND)
        message(FATAL_ERROR "libjpeg library not found")
    endif(NOT JPEG_FOUND)

    #
    # freetype
    #
    find_package(FREETYPE REQUIRED)
    if(NOT FREETYPE_FOUND)
        message(FATAL_ERROR "freetype library not found")
    endif(NOT FREETYPE_FOUND)
endif(TEST_STATIC)

#
# PoDoFo
#
find_path(PODOFO_INCLUDE NAMES "podofo/podofo.h")
find_library(PODOFO_LIBRARY NAMES podofo)
if(NOT PODOFO_INCLUDE)
    message(FATAL_ERROR "PoDoFo include path not found")
else(NOT PODOFO_INCLUDE)
    message(STATUS "Found PoDoFo include path: ${PODOFO_INCLUDE}")
endif()
if(NOT PODOFO_LIBRARY)
    message(FATAL_ERROR "PoDoFo library not found")
else(NOT PODOFO_LIBRARY)
    message(STATUS "Found PoDoFo library: ${PODOFO_LIBRARY}")
endif()

if(NOT TEST_STATIC)
    add_subdirectory(xalan-c)
    add_subdirectory(xerces-c)
    add_subdirectory(libgd)
    add_subdirectory(geos)
    add_subdirectory(gdal)
    add_subdirectory(cppunit)
    add_subdirectory(podofo)
else()
    add_subdirectory(cppunit)
    add_subdirectory(podofo)
endif()
