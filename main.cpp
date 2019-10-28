#include <iostream>
#include "parser.h"

int main(int argc, char **argv) {
  std::ifstream in;
  in.open("in.txt");
  parser a(in);

  return 0;
}