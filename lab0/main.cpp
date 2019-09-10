#include <fstream>
#include <map>
#include "table.h"

int main(int argc, char **argv) {
  using namespace std;

  table table;

  ifstream in;
  in.open(argv[1]);
  ofstream out;
  out.open(argv[2]);

  string inStr;

  while (getline(in, inStr)) {
    table.eraseStr();
    for (char &c : inStr) {
      if (isalpha(c) || (isdigit(c)))
        table.addSimbol(c);
      else {
        table.wordHandler();
      }
    }
    table.wordHandler();
  }

  table.print(out);

  in.close();
  out.close();
  return 0;
}
