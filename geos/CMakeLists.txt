project(geostest CXX)

include_directories(${GEOS_INCLUDE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(geostest_SOURCES "main.cpp")

add_executable("${PROJECT_NAME}" "${geostest_SOURCES}")

target_link_libraries(${PROJECT_NAME} ${GEOS_LIBRARY})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/${PROJECT_NAME}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/${PROJECT_NAME}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/${PROJECT_NAME}/bin"
)