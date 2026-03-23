#include <array>
#include <cstdio>
#include <memory>
#include <sstream>
#include <utility>

#include "command_runner.h"

namespace {

std::string shell_escape(const std::string& value) {
  std::string escaped = "'";

  for (char character : value) {
    if (character == '\'') {
      escaped += "'\\''";
      continue;
    }

    escaped += character;
  }

  escaped += "'";
  return escaped;
}

std::string build_shell_command(const std::string& shell,
                                const std::vector<std::string>& shell_args,
                                const std::string& command) {
  std::ostringstream invocation;
  invocation << shell_escape(shell);

  for (const std::string& arg : shell_args) {
    invocation << ' ' << shell_escape(arg);
  }

  invocation << ' ' << shell_escape(command);
  return invocation.str();
}

}  // namespace

CommandRunner::CommandRunner(std::string shell,
                             std::vector<std::string> shell_args)
    : shell_(std::move(shell)), shell_args_(std::move(shell_args)) {}

void CommandRunner::set_shell(const std::string& shell,
                              const std::vector<std::string>& args) {
  shell_ = shell;
  shell_args_ = args;
}

std::string CommandRunner::run(const std::string& command) const {
  const std::string invocation =
      build_shell_command(shell_, shell_args_, command);
  struct PipeCloser {
    void operator()(FILE* pipe) const {
      if (pipe != nullptr) {
        pclose(pipe);
      }
    }
  };

  std::unique_ptr<FILE, PipeCloser> pipe(popen(invocation.c_str(), "r"));

  if (!pipe) {
    return {};
  }

  std::array<char, 256> buffer{};
  std::ostringstream output;

  while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
    output << buffer.data();
  }

  return output.str();
}
