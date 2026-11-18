# Agents

## Commands

**Build:**
```
make build
```

**Run:**
```
make run
```

**Test:**
```
make test
```

**Clean:**
```
make clean
```

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for dev container setup, make commands, TDD workflow, and how to work with ADRs.

See [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) for community standards.

## Architecture decisions

Our architecture decisions live in `docs/adr/`. Read them before changing the build system, tooling, or test setup.

## Rules

- Never go against an accepted ADR. To change a decision, write a new ADR with status `Proposed` and ask the user.
- Never set an ADR status to `Accepted`.
- Prefix all private member variables with `_`.
- Do not prefix accessor functions with `get`; name them after the value they return.
- Group source files by concept under `src/<concept>/` and tests under `tests/<concept>/`; update includes and build configuration when moving files.
- Prefer simple, beginner-friendly C++ over unnecessary complexity.
- Do not run `make build`, `make test`, or `make run` unless explicitly requested; the user will run them.
