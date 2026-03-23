# Title
Replace recursive REPL dispatch with an explicit iterative loop

## Problem
Interactive execution currently works by recursively calling `dispatch()` after each input line.

Even though the code is short, recursion is a poor fit for an unbounded interactive session.

## Why this is valuable
- Makes the control flow easier to read.
- Avoids unnecessary stack growth across long REPL sessions.
- Makes exit, error, and interruption behavior easier to reason about.
- Sets up cleaner hooks for future interactive features.

## Proposed scope
- Replace the recursive REPL pattern with a loop-based implementation.
- Keep command behavior the same unless a small behavior fix is needed.
- Make exit conditions explicit and centralized.

## Acceptance criteria
- REPL mode uses a loop, not recursive command dispatch.
- Exit commands and EOF handling are explicit in one obvious place.
- The resulting control flow is simpler to read than the current implementation.

## Implementation notes
This should stay small. The goal is not a new architecture, only a safer and clearer interaction loop.
