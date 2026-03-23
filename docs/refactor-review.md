# Refactor review: long-term simplicity, maintainability, and testability

This repository is a small and useful starting point, but several design choices that are fine for a quick template will become expensive once real application logic is added.

The highest-value themes are:

1. **Separate framework code from example/demo behavior.**
2. **Move logic away from direct process and console side effects.**
3. **Create smaller, more composable interfaces with explicit responsibilities.**
4. **Build a real test seam before the codebase grows.**

## Highest-priority observations

### 1. `main.cpp` mixes template scaffolding with runtime behavior
The current entry point both runs the CLI and then unconditionally executes `ls .` through `CommandRunner`.

Why this matters:
- It makes the template feel less like a reusable application skeleton and more like a demo.
- It hides the true application lifecycle.
- It creates surprising side effects for users who copy this template.
- It makes future startup flow harder to reason about and test.

### 2. `CLI` combines parsing, dispatch, REPL flow, and console I/O
`CLI` currently owns:
- argc/argv translation
- REPL state
- command dispatch
- help/version rendering
- unknown-command behavior
- direct `std::cin` / `std::cout` usage

Why this matters:
- The class is small now, but every new feature will compound complexity in one place.
- Behavior is difficult to unit test because control flow and side effects are tightly coupled.
- There is no clean seam for adding command metadata, auto-generated help, or alternate front ends.

### 3. `dispatch()` uses recursion for REPL execution
The recursive call pattern is elegant for a toy example, but it is the wrong long-term shape for an interactive loop.

Why this matters:
- The control flow is less obvious than a loop.
- Long sessions can keep growing the call stack.
- Exit and error handling are harder to model cleanly.

### 4. `CommandRunner` only returns stdout and hides process outcomes
The command runner currently returns a `std::string`, does not expose exit status, and does not capture stderr.

Why this matters:
- Callers cannot tell success from failure reliably.
- Tests cannot assert process outcomes precisely.
- Production code will eventually need richer behavior than "give me stdout text".

### 5. Shell-based command execution is the only execution API
The current API is shell-first (`bash -c`) instead of argument-first.

Why this matters:
- It encourages stringly-typed command construction.
- It increases quoting and escaping complexity.
- It makes it easier to accidentally introduce command-injection bugs later.
- It is harder to test deterministic process invocations.

### 6. The template does not yet provide meaningful automated coverage
The only current test is a sanity assertion.

Why this matters:
- The most reusable template components (`CLI`, `CommandRunner`) have no regression protection.
- Refactors will feel risky.
- Consumers of the template do not get a strong example of how to test their own code.

### 7. Build structure does not yet reflect the architectural intent
The executable target owns all implementation, while tests do not link the core application code as a reusable library.

Why this matters:
- It becomes awkward to test real behavior without duplicating setup.
- It encourages application logic to live only inside the executable target.
- It limits reuse if the template grows into multiple binaries or integration tests.

## Recommended issue order

Recommended execution order for the attached issue drafts:

1. Remove demo side effects from `main`.
2. Split CLI parsing/dispatch/REPL responsibilities.
3. Replace recursive REPL flow with an explicit loop.
4. Introduce injectable input/output streams for CLI.
5. Add a structured command result for `CommandRunner`.
6. Add a non-shell, argv-based process API.
7. Restructure CMake around a reusable core library.
8. Build real tests around CLI and process behavior.
9. Replace ad hoc command strings with a command model/registry.
10. Clean up template surface area and dependency boundaries.

## Deliverables in this folder

The `docs/github-issues/` folder contains issue-ready drafts with:
- a clear title
- problem statement
- value explanation
- concrete scope
- acceptance criteria
- implementation notes

These drafts are intentionally small and straightforward so they can be pasted into GitHub as separate issues without further rewriting.
