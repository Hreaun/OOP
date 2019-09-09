#include <fstream>
#include <iomanip>
#include <map>
#include <set>
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

  typedef function<bool(pair<string, int>, pair<string, int>)> Comparator;

  Comparator compFunctor = [](const pair<string, int> &elem1,
                              const pair<string, int> &elem2) {
    return elem1.second >= elem2.second;
  };

  set<pair<string, int>, Comparator> setOfWords(table.getMapBegin(),
                                                table.getMapEnd(), compFunctor);

  for (const pair<string, int> &element : setOfWords)
    out << element.first << "," << element.second << "," << setprecision(3)
        << element.second / table.getWordCounter() * 100 << "%" << endl;

  in.close();
  out.close();
  return 0;
}
