# set the target name
get_filename_component(CURRENT_FOLDER_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
set(TARGET_NAME ${CURRENT_FOLDER_NAME})


###############################
#                             #
# Sources                     #
#                             #
###############################

# Add source files
set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/gl.c)

# Add header files
set(TARGET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(HEADER_FILES
    ${TARGET_INCLUDE_DIR}/glad/gl.h
    ${TARGET_INCLUDE_DIR}/KHR/khrplatform.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES} ${SOURCE_FILES})


###############################
#                             #
# Library                     #
#                             #
###############################

add_library(${TARGET_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(${TARGET_NAME} PRIVATE ${TARGET_INCLUDE_DIR})

set(GLAD_NAME ${TARGET_NAME} PARENT_SCOPE)
set(GLAD_INCLUDE_DIR ${TARGET_INCLUDE_DIR} PARENT_SCOPE)
