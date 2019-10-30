#ifndef WORKFLOW__GREP_H_
#define WORKFLOW__GREP_H_

#include "readfile.h"
class grep : public readfile{
 public:
  void execute(std::list<std::string> arg) override {
    std::string givenWord = arg.back();
    for (auto it = text.begin(); it != text.end(); it++) {
      if (it->find(givenWord) == std::string::npos){
        text.erase(it);
      }
    }
  }
};

#endif //WORKFLOW__GREP_H_