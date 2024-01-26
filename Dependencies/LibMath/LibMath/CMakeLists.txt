# set the target name
get_filename_component(CURRENT_FOLDER_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
set(TARGET_NAME ${CURRENT_FOLDER_NAME})


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
	${CMAKE_CURRENT_SOURCE_DIR}/*.c++)

# Add header files
set(TARGET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Header)
file(GLOB_RECURSE HEADER_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.inl)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES} ${SOURCE_FILES})


###############################
#                             #
# Executable                  #
#                             #
###############################

if (NOT SOURCE_FILES)
  add_library(${TARGET_NAME} INTERFACE ${HEADER_FILES} ${SOURCE_FILES})
  set(TARGET_COMPILE_OPTIONS_LEVEL INTERFACE)
else()
  add_library(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})
  set(TARGET_COMPILE_OPTIONS_LEVEL PRIVATE)
endif()

include_directories(${TARGET_INCLUDE_DIR})

if(MSVC)
  target_compile_options(${TARGET_NAME} ${TARGET_COMPILE_OPTIONS_LEVEL} /W4 /WX)
else()
  target_compile_options(${TARGET_NAME} ${TARGET_COMPILE_OPTIONS_LEVEL} -Wall -Wextra -Wpedantic -Werror)
endif()

set(LIBMATH_NAME ${TARGET_NAME} PARENT_SCOPE)
set(LIBMATH_INCLUDE_DIR ${TARGET_INCLUDE_DIR} PARENT_SCOPE)
