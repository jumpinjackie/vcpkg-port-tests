project(CreateDOMDocument CXX)

include_directories(${XERCESC_INCLUDE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CreateDOMDocument_SOURCES "CreateDOMDocument.cpp")

add_executable("${PROJECT_NAME}" "${CreateDOMDocument_SOURCES}")

target_link_libraries(${PROJECT_NAME} optimized ${XERCESC_LIBRARY_RELEASE} debug ${XERCESC_LIBRARY_DEBUG})