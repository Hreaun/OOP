#include <iostream>
#include "commandExecuter.h"

int main(int argc, char **argv) {
  std::ifstream in;
    in.open(argv[1]);
  if(!in) {
      std::cerr << "Cannot open the file\n";
      return -1;
  }
  parser a;
  a.parse(in);

  commandExecuter cmd;
  cmd.exe(a.getScheme(), a.getSequence());

  return 0;
}
