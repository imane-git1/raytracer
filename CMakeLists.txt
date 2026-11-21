cmake_minimum_required(VERSION 3.20)
project(raytracer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Core library: everything except main(), shared by the app and the tests
add_library(raytracer_core
  src/math/vector.cpp
  src/geometry/ray.cpp
  src/geometry/sphere.cpp
  src/geometry/plane.cpp
  src/scene/scene.cpp
  src/material/material.cpp
  src/render/camera.cpp
  src/render/trace.cpp
  src/colour/colour.cpp
  src/image/image.cpp
  src/io/png_saver.cpp
)
target_include_directories(raytracer_core PUBLIC src)

# Main executable
add_executable(raytracer src/main.cpp)
target_link_libraries(raytracer PRIVATE raytracer_core)

# Testing
include(FetchContent)
FetchContent_Declare(
  lodepng
  GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
  GIT_TAG        7b2893e35891c0c85bee5595caafaf3c2044b409
)
FetchContent_MakeAvailable(lodepng)
add_library(lodepng STATIC ${lodepng_SOURCE_DIR}/lodepng.cpp)
target_include_directories(lodepng PUBLIC ${lodepng_SOURCE_DIR})
target_link_libraries(raytracer_core PRIVATE lodepng)

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
  tests/material/test_material.cpp
  tests/geometry/test_ray.cpp
  tests/geometry/test_sphere.cpp
  tests/geometry/test_plane.cpp
  tests/scene/test_scene.cpp
  tests/image/test_image.cpp
  tests/image/test_png_saver.cpp
  tests/math/test_vector.cpp
  tests/render/test_camera.cpp
  tests/render/test_trace.cpp
)
target_include_directories(raytracer_tests PRIVATE tests ${lodepng_SOURCE_DIR})
target_link_libraries(raytracer_tests PRIVATE raytracer_core Catch2::Catch2WithMain lodepng)

include(CTest)
include(Catch)
catch_discover_tests(raytracer_tests)
