# Title
Inject CLI input/output streams instead of hard-coding `std::cin` and `std::cout`

## Problem
`CLI` directly reads from `std::cin` and writes to `std::cout`.

That makes behavior harder to test and harder to reuse in contexts where input/output should be redirected.

## Why this is valuable
- Greatly improves testability.
- Allows deterministic tests for prompts, help text, version output, and unknown-command behavior.
- Makes the CLI easier to embed in alternate front ends or scripted environments.

## Proposed scope
- Allow `CLI` to receive input and output streams through constructor parameters or a small configuration object.
- Keep defaults as standard streams so the normal user experience does not change.
- Update methods to write through the injected streams rather than directly to globals.

## Acceptance criteria
- `CLI` can be instantiated with custom input/output streams in tests.
- Help/version/error output can be asserted without touching global process streams.
- Interactive input can be simulated with string streams.

## Implementation notes
Keep the public API simple. A pair of stream references or a small I/O context object is enough.
