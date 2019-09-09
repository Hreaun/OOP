#ifndef TASK0B_TABLE_H
#define TASK0B_TABLE_H

#include <map>
#include <string>

using namespace std;
class table {
private:
  double wordCounter;
  string currentStr;
  map<string, int> word;

public:
  table() {
    wordCounter = 0;
    currentStr = {};
  }

  double getWordCounter() { return wordCounter; }

  auto getMapBegin() { return word.begin(); }

  auto getMapEnd() { return word.end(); }

  void eraseStr() { currentStr = {}; }

  void addSimbol(char c) { currentStr += c; }

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
