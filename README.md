# Raytracing Live Demo 2026

A C++ raytracer built incrementally during the course, using TDD.

[![CI](https://github.com/[ORG]/raytracing-live-demo-2026/actions/workflows/ci.yml/badge.svg)](https://github.com/[ORG]/raytracing-live-demo-2026/actions/workflows/ci.yml)

Licence: [MIT](LICENSE) · [Contributing](CONTRIBUTING.md) · [Code of Conduct](CODE_OF_CONDUCT.md)

---

## Project structure

```
.
├── .devcontainer/      # Dev container config (VSCode / Zed)
├── src/
│   ├── main.cpp        # Main entry point
│   └── math/
│       ├── vector.h    # 3D vector declaration
│       └── vector.cpp  # 3D vector implementation
├── tests/
│   ├── test_main.cpp   # Catch2 unit tests
│   └── math/
│       └── test_vector.cpp
└── CMakeLists.txt
```

---

## Cross-platform setup

### Option A — Dev container (recommended)

Requires [Docker](https://www.docker.com/) and either:
- **VS Code** with the [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension, or
- **Zed** with its built-in dev container support.

1. Open the repository folder in VS Code or Zed.
2. When prompted, click **"Reopen in Container"** (VS Code) or **"Use Dev Container"** (Zed).
3. The container image provides GCC, CMake ≥ 3.20, and Git. Catch2 is downloaded automatically at first build.
4. CMake configures and builds automatically on container creation (`postCreateCommand`).

### Option B — Native (macOS / Linux / Windows)

Prerequisites:
| Tool | Minimum version |
|------|----------------|
| CMake | 3.20 |
| C++ compiler | GCC 12 / Clang 15 / MSVC 19.34 (C++20) |
| Git | any recent |

---

## Common commands

| Command | What it does |
|---------|-------------|
| `make build` | Configure + compile everything |
| `make run` | Build then launch the raytracer |
| `make test` | Build then run the test suite |
| `make clean` | Delete the `build/` directory |

`run` and `test` both depend on `build`, so they recompile automatically if sources have changed.

---

## Building

```bash
make build
```

<details>
<summary>Raw CMake (if you prefer)</summary>

```bash
# Configure (only needed once, or after changing CMakeLists.txt)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

# Build everything (main binary + test binary)
cmake --build build
```
</details>

---

## Running the Hello World demo

```bash
make run
# Hello, Raytracer!
```

---

## Running the tests

```bash
make test
```

<details>
<summary>More verbose output</summary>

```bash
# Run the test binary directly for Catch2's reporter
./build/tests --reporter compact
```
</details>

You should see:

```
All tests passed (2 assertions in 2 test cases)
```

---

## Test-driven development workflow

Tests live in `tests/`. Add a new `TEST_CASE` before writing the implementation, confirm it fails, then implement until it passes.

```cpp
// tests/test_vec3.cpp  (example)
#include <catch2/catch_test_macros.hpp>
#include "vec3.h"

TEST_CASE("Vec3 dot product", "[vec3]") {
    Vec3 a{1, 0, 0};
    Vec3 b{0, 1, 0};
    REQUIRE(dot(a, b) == 0.0f);
}
```

Useful Catch2 macros:

| Macro | Purpose |
|-------|---------|
| `REQUIRE(expr)` | Assert; stop test on failure |
| `CHECK(expr)` | Assert; continue on failure |
| `REQUIRE_THROWS(expr)` | Expect an exception |
| `Catch::Approx(x).epsilon(e)` | Floating-point comparison |

Full docs: https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md

---

## Adding new source files

1. Create files under a concept folder, such as `src/math/yourfile.cpp` and optionally `src/math/yourfile.h`.
2. Add it to `CMakeLists.txt`:
   ```cmake
   target_sources(raytracer PRIVATE src/math/yourfile.cpp)
   ```
3. Add its test under the matching folder in `tests/`, such as `tests/math/test_yourfile.cpp`, and add it similarly to the `tests` target:
   ```cmake
   target_sources(tests PRIVATE tests/math/test_yourfile.cpp)
   ```
