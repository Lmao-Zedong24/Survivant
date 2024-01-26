cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_FOLDER ${CMAKE_FOLDER}/LibMath)

# set solution
project(LibMath LANGUAGES CXX)

option(LIBMATH_BUILD_TESTS "Build the LibMath test programs" ON)

# include subdirectories
add_subdirectory(LibMath)

if (LIBMATH_BUILD_TESTS)
  enable_testing()

  add_subdirectory(LibMath_UnitTest)

  if(MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT LibMath_UnitTest)
  endif()
endif()