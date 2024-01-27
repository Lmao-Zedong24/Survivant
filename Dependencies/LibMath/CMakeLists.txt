set(CMAKE_FOLDER ${CMAKE_FOLDER}/LibMath)

option(LIBMATH_BUILD_TESTS "Build the LibMath test programs" ON)

# include subdirectories
add_subdirectory(LibMath)

if (LIBMATH_BUILD_TESTS)
  enable_testing()
  add_subdirectory(LibMath_UnitTest)
endif()

set(LIBMATH_NAME ${LIBMATH_NAME} PARENT_SCOPE)
set(LIBMATH_INCLUDE_DIR ${LIBMATH_INCLUDE_DIR} PARENT_SCOPE)