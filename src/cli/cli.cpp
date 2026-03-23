#include <sstream>
#include <utility>

#include "cli.h"

namespace {

bool is_exit_command(const std::string& command) {
  return command == "exit" || command == "quit";
}

std::vector<std::string> tokenize(const std::string& line) {
  std::istringstream input(line);
  std::vector<std::string> tokens;

  for (std::string token; input >> token;) {
    tokens.push_back(std::move(token));
  }

  return tokens;
}

}  // namespace

CLI::CLI(std::string version, std::istream& input, std::ostream& output)
    : input_(input), output_(output), version_(std::move(version)) {}

int CLI::run(int argc, char** argv) {
  std::vector<std::string> args(argv + 1, argv + argc);

  if (!args.empty()) {
    if (is_exit_command(args.front())) {
      return 0;
    }

    return dispatch(args);
  }

  return run_repl();
}

int CLI::dispatch(const std::vector<std::string>& args) {
  if (args.empty()) {
    return 0;
  }

  const std::string& command = args[0];
  std::vector<std::string> sub_args(args.begin() + 1, args.end());

  if (command == "--help" || command == "help") {
    show_help();
    return 0;
  }

  if (command == "--version" || command == "version") {
    show_version();
    return 0;
  }

  handle_command(command, sub_args);
  return 0;
}

void CLI::handle_command(const std::string& cmd,
                         const std::vector<std::string>& args) {
  output_ << "Unknown command: " << cmd << "\n";
  show_help();
}

void CLI::show_help() {
  output_ << "Available commands:\n"
          << "  help        Show this help message\n"
          << "  version     Show version info\n"
          << "  exit        Exit the REPL\n"
          << "\nUsage:\n"
          << "  <command> [args...]\n";
}

void CLI::show_version() { output_ << "Version: " << version_ << "\n"; }

int CLI::run_repl() {
  while (true) {
    output_ << "> ";

    std::string line;
    if (!std::getline(input_, line)) {
      return 0;
    }

    std::vector<std::string> tokens = tokenize(line);
    if (tokens.empty()) {
      continue;
    }

    if (is_exit_command(tokens.front())) {
      return 0;
    }

    dispatch(tokens);
  }
}
