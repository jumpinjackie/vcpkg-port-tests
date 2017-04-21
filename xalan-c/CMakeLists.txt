project(xalantest CXX)

include_directories(${XALANC_INCLUDE})
include_directories(${XERCESC_INCLUDE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
link_libraries(${XALANC_LIBRARY})
link_libraries(${XERCESC_LIBRARY})

set(xalantest_SOURCES "main.cpp")

add_executable("${PROJECT_NAME}" "${xalantest_SOURCES}")