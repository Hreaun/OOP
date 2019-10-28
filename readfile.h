#ifndef WORKFLOW__READFILE_H_
#define WORKFLOW__READFILE_H_
#include <iostream>
#include "iWorker.h"

class readfile : public iWorker{
 public:
  static std::list <std::string> text;
 public:
  void execute(std::list <std::string> arg) override{
    std::ifstream in;
    in.open(arg.back());
    std::string str;
    while(getline(in, str)) {
      text.push_back(str);
    }
  }
};

std::list <std::string> readfile::text = {};

#endif //WORKFLOW__READFILE_H_