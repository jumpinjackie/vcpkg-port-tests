project(CreateDOMDocument CXX)

include_directories(${XERCESC_INCLUDE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CreateDOMDocument_SOURCES "CreateDOMDocument.cpp")

add_executable("${PROJECT_NAME}" "${CreateDOMDocument_SOURCES}")

target_link_libraries(${PROJECT_NAME} ${XERCESC_LIBRARY})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/${PROJECT_NAME}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/${PROJECT_NAME}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/${PROJECT_NAME}/bin"
)