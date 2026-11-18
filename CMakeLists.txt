cmake_minimum_required(VERSION 3.20)
project(raytracer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Core library: everything except main(), shared by the app and the tests
add_library(raytracer_core
  src/math/vector.cpp
  src/geometry/ray.cpp
  src/geometry/sphere.cpp
  src/render/camera.cpp
  src/render/trace.cpp
  src/colour/colour.cpp
)
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

add_executable(raytracer_tests
  tests/test_helpers.cpp
  tests/test_main.cpp
  tests/colour/test_colour.cpp
  tests/geometry/test_ray.cpp
  tests/geometry/test_sphere.cpp
  tests/math/test_vector.cpp
  tests/render/test_camera.cpp
  tests/render/test_trace.cpp
)
target_include_directories(raytracer_tests PRIVATE tests)
target_link_libraries(raytracer_tests PRIVATE raytracer_core Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(raytracer_tests)
