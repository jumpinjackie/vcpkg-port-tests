project(CreateDOMDocument CXX)

include_directories(${XERCESC_INCLUDE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
link_libraries(${XERCESC_LIBRARY})

set(CreateDOMDocument_SOURCES "CreateDOMDocument.cpp")

add_executable("${PROJECT_NAME}" "${CreateDOMDocument_SOURCES}")