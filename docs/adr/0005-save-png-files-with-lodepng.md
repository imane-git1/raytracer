# 5. Save PNG files with LodePNG

## Status 

Accepted

## Context

The renderer produces an `Image` in memory. The client's artists need a file they can open and that tests can read back. Our criteria are: a licence that fits an open-source project, nothing to install, easy CMake integration, a readable C++ interface, and an actively maintained project.

Options considered:

- **Hand-written PPM file.** The simplest format to write ourselves. Our first 400 by 300 image is 735 bytes as a PNG, while its pixels alone, uncompressed, take 400 × 300 × 3 = 360,000 bytes.
- **libpng** and **stb_image_write.** Considered, but LodePNG gives us what we need with less setup.
- **LodePNG.** The library is one source file and one header (`lodepng.cpp` and `lodepng.h`), has a `std::vector` based interface, is released under the zlib licence, and needs no other library.

## Decision

We use LodePNG, pinned to commit `7b2893e35891c0c85bee5595caafaf3c2044b409`, fetched with CMake `FetchContent` and built as a static library that `raytracer_core` links to privately.

We hide it behind our own `ImageSaver` interface, with `PngSaver` as the first implementation. Only `main.cpp` creates a `PngSaver`. Adding another format, such as EXR, then means writing one new class. This ADR is the reason `ImageSaver` exists before a second implementation does.

## Consequences

- Nothing to install: the library is downloaded at configure time.
- In production code, only `png_saver.cpp` includes LodePNG, so changing the library or the format touches one class. The tests also use it to read the PNG back.
- The zlib licence allows us to use the library in an open-source project.
- We depend on one more external library. The pinned commit keeps builds reproducible, but configuring needs network access.
- `ImageSaver` adds an abstraction that has a single implementation for now.