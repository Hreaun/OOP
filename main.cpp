#include <iostream>
#include "commandExecuter.h"

int main(int argc, char **argv) {
  std::ifstream in;
  in.exceptions(std::ifstream::failbit);
  try {
    in.open(argv[1]);
  }
  catch (const std::ifstream::failure &ex) {
    std::cerr << "Cannot open the file\n";
  }
  parser a;
  a.parse(in);

  commandExecuter cmdExe;
  cmdExe.exe(a.getScheme(), a.getSequence());

  return 0;
}