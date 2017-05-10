project(unittest CXX)

include_directories(${CPPUNIT_INCLUDE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(unittest_SOURCES "main.cpp")

add_executable("${PROJECT_NAME}" "${unittest_SOURCES}")

target_link_libraries(${PROJECT_NAME} ${CPPUNIT_LIBRARY})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/${PROJECT_NAME}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/${PROJECT_NAME}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/${PROJECT_NAME}/bin"
)