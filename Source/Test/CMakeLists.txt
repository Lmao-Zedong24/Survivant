# set target
get_filename_component(CURRENT_FOLDER_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
set(TARGET_NAME ${PROJECT_NAME}${CURRENT_FOLDER_NAME})

# Setup output directories.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/${TARGET_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/${TARGET_NAME})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})


###############################
#                             #
# Sources                     #
#                             #
###############################

# Add source files
file(GLOB_RECURSE SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.cc # C with classes
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.cxx
	${CMAKE_CURRENT_SOURCE_DIR}/*.c++
)

# Add header files
set(TARGET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB_RECURSE HEADER_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.inl
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES} ${SOURCE_FILES})


###############################
#                             #
# Executable                  #
#                             #
###############################

add_executable(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${TARGET_NAME} PRIVATE ${TARGET_INCLUDE_DIR}
	${LIBMATH_INCLUDE_DIR} ${ENGINE_INCLUDE_DIRS}
	${GLAD_INCLUDE_DIR} ${GLFW_INCLUDE_DIR}
)

target_link_libraries(${TARGET_NAME}
	PRIVATE
	${LIBMATH_NAME}
	${ENGINE_TARGETS}
	${GLAD_NAME} 
	${GLFW_NAME}
)

if(MSVC)
	target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
else()
	target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

copy_resources(${TARGET_NAME})

set(TEST_NAME ${TARGET_NAME} PARENT_SCOPE)