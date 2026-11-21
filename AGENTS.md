# AGENTS.md — C++20 & TDD Rules for AI Assistants

> **Core Role:** The human is Tech Lead and Architect; **you (the AI) do the typing, one small step at a time.**
> The human owns **the numbers, the names, and the next step.** Never modify any file not strictly required by the current step (zero drive-by refactoring).

## 1. Commands (Run from Repository Root)

```bash
make build   # Configure & compile (cmake -S . -B build && cmake --build build)
make run     # Build & run ./build/raytracer
make test    # Build & run Catch2 tests (cd build && ctest --output-on-failure)
make clean   # Remove build/ directory
```

See [CONTRIBUTING.md](CONTRIBUTING.md) and [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md).

## 2. Architecture Decision Records (`docs/adr/`) — Hard Lock

- **Read first:** Read `docs/adr/` before changing `CMakeLists.txt` (structure, flags, dependencies), `Makefile`, tooling, folder layout, or domain interfaces. *(Adding new `.cpp`/`.h` or test files to existing target lists in `CMakeLists.txt` during TDD requires no ADR.)*
- **Never violate an `Accepted` ADR.** To propose a change, create a numbered ADR in `docs/adr/` with `Status: Proposed` (with alternatives in *Context* and downsides in *Consequences*), then **STOP and ask the human**.
- **Never self-approve:** Never write `Status: Accepted` in an ADR. Only the human promotes `Proposed` to `Accepted`.

## 3. Sequential TDD Lock (3-Gate State Machine)

Never write production code and tests in the same step (unless the human explicitly requests a time-boxed spike or says `"go auto"` for a cycle).

1. **Gate 1 — RED & VERIFY RED (Test, Stub & Failure Proof in One Turn):**
   - Write **only** the unit test in `tests/` and a minimal compiling stub in `src/` returning a wrong constant (`0`, `(0,0,0)`, `std::nullopt`). Omit unused parameter names in stubs (`isHitBy(const Ray&) const`) or use `[[maybe_unused]]` for **zero compiler warnings**.
   - **Expected values come from the maths, never from running the code.** Show your math calculation clearly in your message *(unless the human says `"go auto"` for that cycle)*.
   - **Existing tests are specifications:** Never weaken, delete, or alter an existing test assertion to make production code pass without explicit human permission.
   - Use **asymmetric, bug-catching values** (`z != 0`, off-centre origins, odd dimensions like `3x5`, shapes in both orders).
   - **Run `make test` immediately** and show the **exact command and output** proving it compiles with zero warnings and fails on the expected assertion, then **STOP** and wait for human validation before Gate 2.
2. **Gate 2 — GREEN & VERIFY GREEN (Minimal Genuine Code & Pass Proof):**
   - Write the minimum genuine domain/math code in `src/` to pass the test (**never hardcode test inputs/outputs to fake passing; every `if` branch must earn a failing test first**).
   - Run `make test` and show the **exact command and output** proving 100% pass.
3. **Gate 3 — REFACTOR & BREAK-CHECK:**
   - Clean up while keeping tests green and changing **zero numbers in tests**. When asked, perform a mutation check (*break code on purpose* to prove a test catches it, then revert).

## 4. Verifiable OOP & Clean Code Rules

- **Immutable Value Objects:** Domain values (`Vector`, `Colour`, `Ray`) have `private` fields, `const` methods, and **zero public setters** (`normalised()` returns a new `Vector`).
- **Class vs. `struct`:** Use `class` when protecting invariants (`Vector`, `Sphere`, `Image`); use `struct` with default-initialised public fields (`double t = 0.0;`) only for passive data bundles (`Hit`).
- **No raw `new` / `delete`:** Use stack allocation by default, and `std::unique_ptr<T>` (`std::make_unique`, `std::move`) for polymorphic ownership (`Scene` owning `Shape`s).
- **Composition Root in `main.cpp` only:** Once an interface exists (`Shape`, `ImageSaver`), only `main.cpp` instantiates its concrete implementations (`Sphere`, `Plane`, `PngSaver`), and core logic depends only on the abstraction.
- **Composition over inheritance:** A `Shape` *has a* `Material`; never build shape × material inheritance trees.
- **Size & parameter thresholds:** Max **20 lines** per method for orchestration logic, and up to **35 lines** for contiguous mathematical formulas (do not split a single equation into obscure micro-helpers; blank lines and `{}` do not count). Max **3 parameters** per function (use Parameter Objects like `Ray`, `Hit`, `Scene` beyond 3).
- **Ubiquitous language & comments:** Use domain names (`isHitBy`, `hit`, `t`, `trace`, `shade`, `normal`). Write **zero `"what"` comments**. Put interface contracts (`t > t_min`, unit normal) in `.h` headers; in `.cpp` files, only write `"why"` comments (math derivations, tolerances, ADR refs). Delete dead code immediately.

## 5. YAGNI & DRY Guardrails

- **Second-Implementation Rule:** Never create an abstract interface (`Shape`, `ImageSaver`) until its **second concrete implementation** is introduced by a test or an `Accepted` ADR (while only `Sphere` exists, depend on `Sphere` directly; extract `Shape` during refactoring when `Plane` arrives; `Vector` and `Ray` never have interfaces).
- **Nothing goes in until a test needs it:** No speculative methods (`cross()`, `at(t)`) before a test requires them.
- **Rule of Three & Domain DRY:** Do not factor out helpers before **3 real duplications**. DRY applies to domain knowledge, not similar-looking code (`Colour` and `Vector` must remain separate classes). In tests, keep input/expected numbers visible in plain sight.

## 6. C++20 & Raytracer Technical Traps

- **Compiler & `.h`/`.cpp` discipline:** C++20 (`CMAKE_CXX_STANDARD 20`), `-Wall -Wextra -Wpedantic`, zero warnings. Split interface (`.h` with `#pragma once` and minimal includes) from implementation (`.cpp`) by default; trivial 1-line accessors or hot-loop `constexpr` math operators on value objects (`Vector`, `Colour`, `Ray`) may be inlined in `.h` when justified.
- **`[[nodiscard]]`, `const&`, and `explicit`:** Mark pure value-object queries (`[[nodiscard]] Vector normalised() const;`, `dot()`, `length()`, `isHitBy()`) so ignored return values trigger warnings. Pass non-trivial types by `const T&` (prevents copies and object slicing). Mark 1-argument constructors `explicit`.
- **Rule of Zero & Virtual Destructors:** Default to Rule of Zero. Every abstract class **must** declare `virtual ~ClassName() = default;`.
- **Default Member Initialisation & Optionality:** Always default-initialise primitive members (`double x = 0.0;`) to prevent Undefined Behaviour. Return `std::optional<Hit>` when a ray may miss (never `null`, `-1`, or out-parameters).
- **Floating-Point & Raytracer Epsilons:**
  - **Never compare `double` with `==` or bare `.epsilon()` near zero:** use `REQUIRE_THAT(actual, Catch::Matchers::WithinAbs(expected, 1e-6))` (from `<catch2/matchers/catch_matchers_floating_point.hpp>`) or `Catch::Approx(expected).margin(1e-6)` so expected `0.0` values do not fail on floating-point noise.
  - **Self-intersection bias (`t_min`):** Enforce `t > t_min` (e.g., `1e-4`) on ray hits to prevent shadow/reflection acne.
  - **Integer division:** Cast `int` to `double` before dividing (`static_cast<double>(width)`).
  - **Operators:** Overload `+`, `-`, `*` only when unambiguous (`origin + t * direction`); use named methods for `dot()` and `cross()`.

## Source layout

New classes go in the folder of their concept under `src/` (`math`, `colour`, `geometry`, `material`, `scene`, `render`, `image`, `io`). Their tests go in the matching folder under `tests/`. Includes start from `src/`, for example `#include "math/vector.h"`. See ADR 0008.

## How we work

- Test-driven development: write the test first, see it fail for the right reason, then make it pass.
- Expected values come from the maths. Ask before changing an expected value in a test.
- One small step at a time. Change only what the current step requires.
- Simple C++: no feature that the current step does not need.
- Build and run only in the dev container, never on the host.