# Title
Return a structured result from `CommandRunner` instead of only stdout text

## Problem
`CommandRunner::run()` currently returns only a `std::string` containing stdout.

That hides important execution details like:
- exit code
- stderr output
- whether process launch itself failed

## Why this is valuable
- Makes command execution useful beyond trivial happy paths.
- Lets callers distinguish success from failure without parsing output text.
- Supports stronger tests and clearer error handling.
- Creates room for richer diagnostics later without breaking every caller again.

## Proposed scope
Introduce a small result type, for example containing:
- stdout text
- stderr text
- exit code
- a success helper or explicit status field

Update `run()` to return that result.

## Acceptance criteria
- Callers can inspect both output streams and exit status.
- Failure handling does not rely on string inspection.
- The API remains small and approachable for template users.

## Implementation notes
Keep the result object minimal. Avoid adding timeouts, environment overrides, and advanced process configuration in this issue unless they are already needed for the refactor.
