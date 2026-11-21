# 9. A colour is its own class

## Status

Accepted

## Context

A colour and a vector are both three numbers. We had to decide whether `Colour` is a `Vector` or a separate class.

## Decision

`Colour` is its own class, with `r()`, `g()` and `b()`, each between 0 and 1. It does not reuse `Vector`.

## Alternatives

Reusing `Vector` for colours: it saves a class, but a colour would then have `x()`, `dot()`, `length()` and `normalised()`, which mean nothing for a colour, and a position could be added to a colour by mistake.

## Consequences

- The compiler rejects a mix-up between a position and a colour.
- Colour operations (such as scaling by a brightness) can evolve without touching `Vector`.
- Some code looks similar in both classes.
