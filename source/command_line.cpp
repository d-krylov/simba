#include "command_line.h"
#include "global.h"
#include <cstdlib>
#include <iostream>

CommandLine::CommandLine(int argc, char **argv) {

  if (argc == 1) {
    Help();
    std::exit(EXIT_FAILURE);
  }
}

void CommandLine::Help() {
  std::cout << "Help: "
            << "\n Usage: ./simba [options] input"
            << "\n Options:"
            << "\n  -o           output file name"
            << "\n  -c           run in concurrency mode" << std::endl;
}