# C++ Template

To skip the annoying part, and get to the good stuff.

Gives a simple CLI interface, and a helper function to perform
command line commands from within your application

For the best experience, install "just" and "Ninja".

## Contains
### CMakeLists
Boilerplate to add an executable target, a reusable core library target, and a lightweight unit test target.

### CLI class
A class which is meant to be subclassed from.

The entrypoint which should not be overridden is run(...).
It will parse input args and then send them to dispatch(...).
dispatch(...) will either go into REPL mode if the app is called
with no arguments. Otherwise, it simply passes the command to one
of three functions meant to be overridden:
1. handle_command(...): Should handle most commands
2. show_help(...): Show something helpful
3. show_version(...): Show the app version

Likely, the show_version(...) function will never really need to be overridden.

### CommandRunner class
Simple class that stores the shell and shell args, lets you update that configuration, and exposes a run command to execute shell commands.

Example usage is cmdRunner.run_command("cat ~/.bashrc") > returns a std::string with that file's content.

### Justfile
A command handler file, for the app "just".

Allows you to do

1. just clean
2. just build
3. just rebuild
4. just run <args>

and you could of course always add more. Just a convenient tool.
