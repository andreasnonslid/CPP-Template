#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "cli.h"
#include "command_runner.h"

namespace {

void expect(bool condition, const std::string& message) {
  if (!condition) {
    throw std::runtime_error(message);
  }
}

class TestCLI : public CLI {
public:
  TestCLI(std::istream& input, std::ostream& output)
      : CLI("1.2.3", input, output) {}

  void handle_command(const std::string& cmd,
                      const std::vector<std::string>& args) override {
    handled_command = cmd;
    handled_args = args;
    output_ << "handled:" << cmd << '\n';
  }

  std::string handled_command;
  std::vector<std::string> handled_args;
};

char app_name[] = "app";
char* help_argv[] = {app_name, const_cast<char*>("help")};
char* version_argv[] = {app_name, const_cast<char*>("version")};
char* custom_argv[] = {app_name, const_cast<char*>("deploy"),
                       const_cast<char*>("prod"), const_cast<char*>("blue")};

void help_command_writes_to_configured_output() {
  std::istringstream input;
  std::ostringstream output;

  CLI cli("1.2.3", input, output);

  expect(cli.run(2, help_argv) == 0, "help command should return success");
  expect(output.str().find("Available commands:") != std::string::npos,
         "help output should contain the command list");
  expect(output.str().find("exit        Exit the REPL") != std::string::npos,
         "help output should document the exit command");
}

void version_command_writes_configured_version() {
  std::istringstream input;
  std::ostringstream output;

  CLI cli("1.2.3", input, output);

  expect(cli.run(2, version_argv) == 0,
         "version command should return success");
  expect(output.str() == "Version: 1.2.3\n",
         "version output should match the configured version");
}

void unknown_commands_are_delegated_to_subclass_handler() {
  std::istringstream input;
  std::ostringstream output;

  TestCLI cli(input, output);

  expect(cli.run(4, custom_argv) == 0,
         "custom command should return success");
  expect(cli.handled_command == "deploy",
         "custom handler should receive the command name");
  expect(cli.handled_args.size() == 2,
         "custom handler should receive both arguments");
  expect(cli.handled_args[0] == "prod",
         "custom handler should preserve argument order");
  expect(cli.handled_args[1] == "blue",
         "custom handler should preserve trailing arguments");
  expect(output.str() == "handled:deploy\n",
         "custom handler should write to the configured output stream");
}

void repl_uses_loop_until_exit_command() {
  std::istringstream input("help\nquit\n");
  std::ostringstream output;

  CLI cli("1.2.3", input, output);

  char* argv[] = {app_name};
  expect(cli.run(1, argv) == 0, "repl should return success");

  const std::string transcript = output.str();
  expect(transcript.find("> Available commands:") != std::string::npos,
         "repl should print help after the prompt");
  expect(std::count(transcript.begin(), transcript.end(), '>') >= 2,
         "repl should prompt for each iteration until exit");
}

void repl_skips_blank_lines_without_failing() {
  std::istringstream input("\nversion\nexit\n");
  std::ostringstream output;

  CLI cli("9.9.9", input, output);

  char* argv[] = {app_name};
  expect(cli.run(1, argv) == 0, "repl should return success for blank lines");
  expect(output.str().find("Version: 9.9.9\n") != std::string::npos,
         "repl should continue after blank lines");
}

void command_runner_executes_shell_commands() {
  CommandRunner runner;
  expect(runner.run("printf 'hello'") == "hello",
         "command runner should capture command output");
}

}  // namespace

int main() {
  const std::vector<std::pair<std::string, std::function<void()>>> tests = {
      {"help_command_writes_to_configured_output",
       help_command_writes_to_configured_output},
      {"version_command_writes_configured_version",
       version_command_writes_configured_version},
      {"unknown_commands_are_delegated_to_subclass_handler",
       unknown_commands_are_delegated_to_subclass_handler},
      {"repl_uses_loop_until_exit_command", repl_uses_loop_until_exit_command},
      {"repl_skips_blank_lines_without_failing",
       repl_skips_blank_lines_without_failing},
      {"command_runner_executes_shell_commands",
       command_runner_executes_shell_commands},
  };

  std::size_t passed = 0;

  for (const auto& [name, test] : tests) {
    try {
      test();
      ++passed;
      std::cout << "[PASS] " << name << '\n';
    } catch (const std::exception& error) {
      std::cerr << "[FAIL] " << name << ": " << error.what() << '\n';
      return 1;
    }
  }

  std::cout << "Passed " << passed << " tests\n";
  return 0;
}
