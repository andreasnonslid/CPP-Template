# Title
Clean up unused template surface area and tighten dependency boundaries

## Problem
The template currently includes signs of loose boundaries, such as:
- an empty `inc/main.h`
- broad global include configuration
- headers that pull in heavier dependencies than necessary
- runtime examples mixed with framework code

None of these are severe in isolation, but together they make the template noisier than it needs to be.

## Why this is valuable
- Improves approachability for new users.
- Reduces unnecessary coupling.
- Keeps the template focused on the pieces users are expected to extend.
- Makes future maintenance easier by lowering incidental complexity.

## Proposed scope
Perform a small cleanup pass to:
- remove unused headers/files like `inc/main.h` if they serve no purpose
- prefer forward declarations or narrower includes where practical
- move example/demo concerns into docs instead of core runtime code
- tighten target-local include configuration in CMake

## Acceptance criteria
- Unused or placeholder files are removed or justified.
- Header dependencies are no broader than needed.
- The repository presents a cleaner minimal template surface to downstream users.

## Implementation notes
This issue should stay incremental. It is a cleanup pass, not a rewrite.
