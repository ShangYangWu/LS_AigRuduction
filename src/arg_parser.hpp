#pragma once

#include <iostream>
#include <fstream>
#include <string>

struct ArgParser {
  std::string file;
};

inline void PrintError(int argc, char **argv) {
  std::cout << "Command: ";
  for (int i = 0; i < argc; ++i) {
    std::cout << argv[i] << " ";
  }
  std::cout << "is not a legal command.\n";
  std::cout << "Please use: \n";
  std::cout << "  " << argv[0] << " truth\n";
  exit(1);
}

inline ArgParser ParseArgument(int argc, char **argv) {
  if (argc != 2) {
    PrintError(argc, argv);
  }
  ArgParser p;
  p.file = argv[1];

  return p;
}


