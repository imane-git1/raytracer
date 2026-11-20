# 6. Coordinate conventions

## Status 

Accepted

## Context

A ray tracer uses two coordinate systems at the same time: the 3D world that contains the camera and the sphere, and the 2D grid of pixels in the image. They count differently. The image counts rows from the top and the world counts `y` upwards, so mixing them up gives an upside-down or mirrored picture, and a symmetric test image would not reveal it.

## Decision

**World.** `x` points to the right, `y` points up and `z` points forward, away from the camera into the scene. This is a left-handed system.

**Image.** A pixel is identified by `(column, row)`. Columns are counted from the left and rows from the top, both starting at 0. The centre of a pixel is at `+ 0.5` in each direction.

**Conversion.** The camera is the only place that converts a pixel into a point on the screen. It flips the vertical axis, because row 0 is at the top of the image while `y` grows upwards. The image stores its pixels row after row, so the index of a pixel is `row * width + column`.

## Consequences

- The image is upright: a sphere moved up in the world (`y` larger) moves up in the picture.
- Tests use odd and non-square sizes (for example 5 by 3) with an off-centre pixel, to catch swapped or mirrored axes.
- With `z` forward, formulas taken from right-handed textbooks may need a sign change, for example if a cross product is added later.