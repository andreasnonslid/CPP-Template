#include "cli.h"

int main(int argc, char** argv) {
  CLI cli("0.0.1");
  return cli.run(argc, argv);
}
