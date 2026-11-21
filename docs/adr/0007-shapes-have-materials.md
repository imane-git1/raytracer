# 7. A shape has a material

## Status

Accepted

## Context

A surface needs a shape-specific intersection test and a material-specific response to light. Combining every shape and material as subclasses would make each new combination a separate class. A sphere or plane can instead contain one `Material` and delegate shading to it.

## Decision

Use composition: `Sphere` and `Plane` each have a `Material`, and implement the `Shape` interface by returning a `Hit` that contains the hit point, unit normal and material. `Scene` owns polymorphic `Shape` objects and selects the nearest hit.

## Alternatives

Shape and material subclasses could be multiplied, such as `MatteSphere`, `MirrorSphere`, `MattePlane` and `MirrorPlane`. This creates one class per combination and makes runtime material changes impossible.

## Consequences

- Adding a shape requires one class that implements `Shape`; it does not require a subclass for every material.
- Adding a material requires a material implementation or an evolved `Material` contract, independently of the shape classes.
- `trace` depends on `Scene` and `Shape` abstractions rather than concrete sphere or plane geometry.
