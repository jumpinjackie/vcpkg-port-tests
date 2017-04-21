project(xalantest CXX)

include_directories(${XALANC_INCLUDE})
include_directories(${XERCESC_INCLUDE})
link_libraries(${XALANC_LIBRARY})

set(xalantest_SOURCES "main.cpp")

add_executable("${PROJECT_NAME}" "${xalantest_SOURCES}")