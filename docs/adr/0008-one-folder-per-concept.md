# 8. One folder per concept

## Status

Accepted

## Context

All sources started in a flat `src/` folder. With Vector, Colour, Ray, Sphere, Camera, Image and more to come, a flat folder will stop telling a reader where to look.

## Decision

Each concept has its own folder under `src/` (`math`, `colour`, `geometry`, `material`, `scene`, `render`, `image`, `io`). Tests mirror it under `tests/`. Includes start from `src/`, for example `#include "math/vector.h"`. A folder is created with its first class.

## Consequences

- A new developer finds a class by its concept.
- Dependencies between folders can be read from the `#include` lines and must stay acyclic: `math` and `colour` depend on no other folder, `material` on `colour` and `math`, `geometry` on `material` and `math`, `scene` on `geometry` and `math`, `image` on `colour`, `io` on `image`, and `render` on `scene`, `geometry`, `image`, `colour` and `math`.
- Moving a file means updating its includes and `CMakeLists.txt`.
- Not done on purpose: namespaces (until names clash or code is shared with partners), one library per folder (until build times or dependencies need control), and a separate `include/` folder (until we ship a library with public and private headers).
