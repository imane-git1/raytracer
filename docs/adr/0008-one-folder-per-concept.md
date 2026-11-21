# 8. One folder per concept

## Status

Accepted

## Context

All sources started in a flat `src/` folder. With Vector, Colour, Ray, Sphere, Camera, Image and more to come, a flat folder will stop telling a reader where to look.

## Decision

Each concept has its own folder under `src/` (`math`, `colour`, `geometry`, `material`, `scene`, `render`, `image`, `io`). Tests mirror it under `tests/`. Includes start from `src/`, for example `#include "math/vector.h"`. A folder is created with its first class.

## Consequences

- A new developer finds a class by its concept.
- Dependencies between folders can be read and kept acyclic: `render` depends on `geometry`, which depends on `math` and `colour`.
- Moving a file means updating its includes and `CMakeLists.txt`.
- Not done on purpose: namespaces (until names clash or code is shared with partners), one library per folder (until build times or dependencies need control), and a separate `include/` folder (until we ship a library with public and private headers).
