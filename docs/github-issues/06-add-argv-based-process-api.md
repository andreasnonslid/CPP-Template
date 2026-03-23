# Title
Add an argument-based process execution API and de-emphasize shell-first execution

## Problem
The current process runner API is centered on `bash -c`-style command strings.

That is convenient for demos, but it is the wrong default for long-term maintainability and safety.

## Why this is valuable
- Reduces quoting and escaping pitfalls.
- Makes process calls more explicit and deterministic.
- Lowers the risk of command injection when user-provided input is eventually introduced.
- Produces cleaner tests because expected arguments are first-class values.

## Proposed scope
- Add an API that accepts an executable plus a vector of arguments.
- Keep shell-based execution only as a separate, clearly named escape hatch if still needed.
- Update README/examples to prefer the argument-based API.

## Acceptance criteria
- There is a first-class non-shell execution path.
- Shell execution is clearly optional rather than the default model.
- Documentation encourages the safer API first.

## Implementation notes
The initial version can be intentionally small. The value is in choosing the right default abstraction, not in building a full process framework.
