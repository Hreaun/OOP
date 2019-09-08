#ifndef TASK0B_TABLE_H
#define TASK0B_TABLE_H

#include <map>
#include <string>

using namespace std;
class table {
public:
  double wordCounter;
  string currentStr;

  table() {
    wordCounter = 0;
    currentStr = {};
  }

  map<string, int> word;

  void wordHandler() {
    if (!currentStr[0])
      return;
    table::wordCounter++;
    if (!table::word.count(currentStr)) { 
      table::word.insert(make_pair(currentStr, 1));
      currentStr = {};
    } else {
      table::word[currentStr]++;
      currentStr = {};
    }
  }
};

#endif // TASK0B_TABLE_H
