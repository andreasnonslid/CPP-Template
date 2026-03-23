# Title
Split `CLI` into smaller responsibilities for parsing, dispatch, and REPL flow

## Problem
The current `CLI` class combines several jobs:
- argv parsing
- REPL mode detection
- command dispatch
- help/version rendering
- unknown-command handling
- direct console I/O

This is manageable now, but it will become a maintenance hotspot as soon as more commands or flags are added.

## Why this is valuable
- Reduces cognitive load in the core command path.
- Makes future features easier to add without editing one large control-flow method.
- Creates natural seams for unit testing.
- Makes the template a better example of application structure.

## Proposed scope
Refactor toward smaller pieces such as:
- a function or type that converts argv/input lines into tokens or a command request
- a dispatcher that decides which command handler should run
- a REPL loop that only manages interactive iteration

Do not over-engineer this into a full framework. The goal is just to separate responsibilities clearly.

## Acceptance criteria
- `CLI` no longer owns all parsing, dispatch, and loop responsibilities in one flow.
- Parsing logic can be tested independently from interactive console behavior.
- Dispatch logic can be tested independently from argv parsing.
- REPL control flow is isolated enough that future features like prompt customization or history can be added cleanly.

## Implementation notes
Prefer small, boring abstractions over deep inheritance or plugin systems. This template should stay approachable.
