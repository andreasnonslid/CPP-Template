# Title
Remove demo side effects from `main` and make startup behavior explicit

## Problem
The template entry point currently runs the CLI and then always executes `ls .` via `CommandRunner`.

That creates behavior that looks like sample/demo code rather than application scaffolding. It also means the template performs an unrelated shell command every time the binary runs.

## Why this is valuable
- Simplifies the startup path.
- Makes the template safer and less surprising for downstream users.
- Establishes a cleaner foundation for future app initialization.
- Removes behavior that is difficult to justify in production code.

## Proposed scope
Keep this issue intentionally narrow:
- Remove the unconditional `CommandRunner` demo call from `main`.
- Make `main` responsible only for constructing the app and returning its exit code.
- If a command runner example is still desired, move it into README documentation or a dedicated example section rather than runtime behavior.

## Acceptance criteria
- Running the binary no longer executes `ls .` or any other unrelated shell command.
- `main` has one obvious responsibility: start the application and return an exit code.
- Any remaining `CommandRunner` usage in the template is deliberate and documented.

## Implementation notes
This is a very small cleanup, but it has outsized long-term value because it clarifies what the template is actually for.
