project(podofotest)

include_directories(${PODOFO_INCLUDE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(podofotest_SOURCES "main.cpp")

add_executable("${PROJECT_NAME}" "${podofotest_SOURCES}")

set(podofotest_LINK ${PODOFO_LIBRARY})

if(TEST_STATIC)
    target_link_libraries(${PROJECT_NAME} ${PODOFO_LIBRARY} ${ZLIB_LIBRARIES} ${BZIP2_LIBRARIES} ${JPEG_LIBRARIES} ${PNG_LIBRARIES} ${FREETYPE_LIBRARIES} wsock32 ws2_32)
else()
    target_link_libraries(${PROJECT_NAME} ${PODOFO_LIBRARY})
endif()

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/${PROJECT_NAME}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/${PROJECT_NAME}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/${PROJECT_NAME}/bin"
)