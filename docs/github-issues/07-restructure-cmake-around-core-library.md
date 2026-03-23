# Title
Restructure CMake so application code lives in a reusable core library target

## Problem
The current build creates an executable target directly from the source files, while tests do not link against a reusable application library.

This makes the template less flexible as soon as application code grows.

## Why this is valuable
- Encourages better separation between application logic and executable wiring.
- Makes unit tests and future integration tests easier to compose.
- Supports future expansion into multiple binaries or tooling targets.
- Improves maintainability by giving the build graph a clearer shape.

## Proposed scope
- Introduce a library target for core application code.
- Keep `main.cpp` as a thin executable entry point.
- Link tests against the library target instead of duplicating setup assumptions.
- Limit include visibility appropriately with `target_include_directories` and `target_link_libraries`.

## Acceptance criteria
- Core code is built in a reusable library target.
- The executable target is mostly wiring.
- Unit tests link directly against the reusable target.
- Build configuration uses target-scoped settings rather than broad global include configuration where practical.

## Implementation notes
This issue is about structure, not feature work. Avoid broad CMake modernization unless it directly supports the target split.
