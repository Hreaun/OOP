#ifndef WORKFLOW__REPLACE_H_
#define WORKFLOW__REPLACE_H_

#include "readfile.h"
class replace : public readfile{
 public:
  void execute(std::list<std::string> arg) override {
    std::string secondWord = arg.back();
    arg.pop_back();
    std::string firstWord = arg.back();
    size_t index = 0;
    for (auto & i : text) {
      index = 0;
      while (true) {
        index = i.find(firstWord, index);
        if (index == std::string::npos) break;
        i.replace(i.find(firstWord), firstWord.length(), secondWord);
        index += secondWord.length();
      }
    }
  }
};

#endif //WORKFLOW__REPLACE_H_
