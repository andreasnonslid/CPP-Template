#pragma once

#include <iostream>
#include <string>
#include <vector>

class CLI {
public:
  explicit CLI(std::string version,
               std::istream& input = std::cin,
               std::ostream& output = std::cout);

  int run(int argc, char** argv);
  int dispatch(const std::vector<std::string>& args);

protected:
  virtual void handle_command(const std::string& cmd,
                              const std::vector<std::string>& args);
  virtual void show_help();
  virtual void show_version();

  std::istream& input_;
  std::ostream& output_;
  std::string version_;

private:
  int run_repl();
};
