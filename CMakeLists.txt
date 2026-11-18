cmake_minimum_required(VERSION 3.20)
project(raytracer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Core library: everything except main(), shared by the app and the tests
add_library(raytracer_core src/math/vector.cpp)
target_include_directories(raytracer_core PUBLIC src)

# Main executable
add_executable(raytracer src/main.cpp)
target_link_libraries(raytracer PRIVATE raytracer_core)

# Testing
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.7.1
)
FetchContent_MakeAvailable(Catch2)

enable_testing()

add_executable(tests tests/test_main.cpp tests/math/test_vector.cpp)
target_include_directories(tests PRIVATE src/math)
target_link_libraries(tests PRIVATE raytracer_core Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)
