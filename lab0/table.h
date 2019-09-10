#ifndef TASK0B_TABLE_H
#define TASK0B_TABLE_H

#include <fstream>
#include <iomanip>
#include <list>
#include <map>
#include <string>

using namespace std;
class table {
private:
  double wordCounter;
  string currentStr;
  map<string, int> word;
  list<pair<int, string>> listOfWords;

  void mapSort() {
    map<string, int>::iterator it;

    for (it = word.begin(); it != word.end(); ++it)
      listOfWords.emplace_back(make_pair(it->second, it->first));

    listOfWords.sort(greater_equal<>());
  }

public:
  table() {
    wordCounter = 0;
    currentStr = {};
  }

  void eraseStr() { currentStr = {}; }

  void addSimbol(char c) { currentStr += c; }


  void print(ofstream &out) {
    mapSort();

    for (const pair<int, string> &element : listOfWords)
      out << element.second << "," << element.first << "," << setprecision(3)
          << element.first / wordCounter * 100 << "%" << endl;
  }

  void wordHandler() {
    if (!currentStr[0])
      return;
    wordCounter++;
    if (!word.count(currentStr)) {
      word.insert(make_pair(currentStr, 1));
      currentStr = {};
    } else {
      word[currentStr]++;
      currentStr = {};
    }
  }
};

#endif // TASK0B_TABLE_H
