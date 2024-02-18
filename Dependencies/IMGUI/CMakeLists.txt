# Download IMGUI
FetchContent_Declare(
	imgui
	GIT_REPOSITORY https://github.com/ocornut/imgui
	GIT_TAG v1.90.1-docking
	GIT_SHALLOW ON
)

set(BUILD_SHARED_LIBS OFF)

FetchContent_MakeAvailable(imgui)

# set the target name
get_filename_component(CURRENT_FOLDER_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
set(TARGET_NAME ${CURRENT_FOLDER_NAME})


###############################
#                             #
# Sources                     #
#                             #
###############################

# Add source files
file(GLOB SOURCE_FILES 
	${imgui_SOURCE_DIR}/*.cpp
)

list(APPEND SOURCE_FILES ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp)

# Add header files
set(TARGET_INCLUDE_DIR ${imgui_SOURCE_DIR})
file(GLOB HEADER_FILES ${imgui_SOURCE_DIR}/*.h)

list(APPEND HEADER_FILES ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.h)

# Add backends

function(AddBackend BACKEND)
	list(APPEND SOURCE_FILES ${imgui_SOURCE_DIR}/backends/imgui_impl_${BACKEND}.cpp)
	set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)
	list(APPEND HEADER_FILES ${imgui_SOURCE_DIR}/backends/imgui_impl_${BACKEND}.h)
	set(HEADER_FILES ${HEADER_FILES} PARENT_SCOPE)
	message(STATUS "[IMGUI] Added ${BACKEND} backend")
endfunction()

AddBackend(glfw)
AddBackend(opengl3)

###############################
#                             #
# Executable                  #
#                             #
###############################

add_library(${TARGET_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(${TARGET_NAME} PRIVATE ${TARGET_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})

source_group(TREE ${imgui_SOURCE_DIR} FILES ${HEADER_FILES} ${SOURCE_FILES})

if(MSVC)
	target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
else()
	target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

set(IMGUI_NAME ${TARGET_NAME} PARENT_SCOPE)
set(IMGUI_INCLUDE_DIR ${TARGET_INCLUDE_DIR} PARENT_SCOPE)
