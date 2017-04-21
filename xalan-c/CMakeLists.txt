project(xalantest CXX)

include_directories(${XALANC_INCLUDE})
include_directories(${XERCESC_INCLUDE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(xalantest_SOURCES "main.cpp")

add_executable(${PROJECT_NAME} ${xalantest_SOURCES})

target_link_libraries(${PROJECT_NAME} optimized ${XALANC_LIBRARY_RELEASE} debug ${XALANC_LIBRARY_DEBUG})
target_link_libraries(${PROJECT_NAME} optimized ${XERCESC_LIBRARY_RELEASE} debug ${XERCESC_LIBRARY_DEBUG})