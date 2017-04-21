project(gdtest)

include_directories(${GD_INCLUDE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_definitions(-DHAVE_LIBPNG)
set(gdtest_SOURCES "main.c")

add_executable("${PROJECT_NAME}" "${gdtest_SOURCES}")

target_link_libraries(${PROJECT_NAME} ${GD_LIBRARY})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/${PROJECT_NAME}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/${PROJECT_NAME}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/${PROJECT_NAME}/bin"
)