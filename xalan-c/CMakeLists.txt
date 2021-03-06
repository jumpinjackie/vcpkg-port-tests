project(xalantest CXX)

include_directories(${XALANC_INCLUDE})
include_directories(${XERCESC_INCLUDE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(xalantest_SOURCES "main.cpp")

add_executable(${PROJECT_NAME} ${xalantest_SOURCES})

target_link_libraries(${PROJECT_NAME} ${XALANC_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${XERCESC_LIBRARY})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/${PROJECT_NAME}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/${PROJECT_NAME}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/${PROJECT_NAME}/bin"
)

ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/foo.xml $<TARGET_FILE_DIR:${PROJECT_NAME}>
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/foo.xml
    COMMENT "Copying foo.xml to $<TARGET_FILE_DIR:${PROJECT_NAME}>"
)
ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/foo.xsl $<TARGET_FILE_DIR:${PROJECT_NAME}>
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/foo.xsl
    COMMENT "Copying foo.xsl to $<TARGET_FILE_DIR:${PROJECT_NAME}>"
)