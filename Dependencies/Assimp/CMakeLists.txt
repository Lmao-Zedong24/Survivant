# Download assimp
FetchContent_Declare(
	assimp
	GIT_REPOSITORY https://github.com/assimp/assimp
	GIT_TAG v5.3.1
	GIT_SHALLOW ON
)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(BUILD_SHARED_LIBS OFF)
set(ASSIMP_BUILD_TESTS OFF)

set(CMAKE_FOLDER ${CMAKE_FOLDER}/assimp)

FetchContent_MakeAvailable(assimp)

set(ASSIMP_NAME assimp PARENT_SCOPE)
set(ASSIMP_INCLUDE_DIR ${assimp_SOURCE_DIR}/include PARENT_SCOPE)