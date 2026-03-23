# Title
Add real unit tests for `CLI` and `CommandRunner` instead of only a sanity check

## Problem
The repository currently includes only a trivial passing assertion.

The reusable parts of the template have no meaningful regression coverage.

## Why this is valuable
- Increases confidence in refactors.
- Demonstrates good testing patterns for users of the template.
- Prevents regressions in help/version handling, dispatch behavior, and command execution.
- Makes the template more credible as a starting point for real projects.

## Proposed scope
Add focused tests for behavior such as:
- `CLI::run()` argument handling
- help/version command routing
- unknown-command handling
- REPL exit behavior
- `CommandRunner` success and failure cases
- stdout/stderr/exit-code behavior once the result API exists

## Acceptance criteria
- The test suite covers real behavior in `CLI` and `CommandRunner`.
- Tests are deterministic and do not rely on fragile environment assumptions where avoidable.
- The previous one-line sanity check is replaced or supplemented by meaningful coverage.

## Implementation notes
Sequence this after the I/O injection and command-result refactors if possible. Those changes will make the tests much easier to write well.
