# Title
Replace ad hoc command string branching with a simple command model or registry

## Problem
Command handling is currently based on direct string comparisons inside `dispatch()`.

That is fine for two or three built-in commands, but it becomes noisy and repetitive once the command surface grows.

## Why this is valuable
- Centralizes command metadata.
- Simplifies help generation.
- Makes commands easier to add, remove, or test.
- Reduces branching complexity in the CLI dispatcher.

## Proposed scope
Introduce a lightweight command representation, such as:
- command name
- aliases
- description/help text
- handler callback or overridable method binding

Keep it intentionally simple; a map or vector of command definitions is enough.

## Acceptance criteria
- Built-in commands are defined in a central structure rather than spread across conditional branches.
- Help output can draw from the same command metadata source.
- Adding a new command requires less boilerplate than editing multiple places manually.

## Implementation notes
Do not turn this into a large framework or macro system. The goal is just to remove stringly-typed branching from the main dispatch path.
