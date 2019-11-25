#ifndef WORKFLOW__READFILE_H_
#define WORKFLOW__READFILE_H_
#include <iostream>
#include "blockFactory.h"

class readfile : public iWorker {
 public:
  void execute(std::list<std::string> arg, std::list<std::string> &text) override {
    if (arg.size() != 2) {
      throw std::logic_error("readfile requires 1 argument.");
    }
    std::ifstream in;
    in.exceptions(std::ifstream::failbit);
    try {
      in.open(arg.back());
    }
    catch (const std::ifstream::failure &ex) {
      std::cerr << "Cannot open the file in readfile\n";
    }

    std::string str;
    while(!(getline(in, str)).eof()){
        text.push_back(str);
    }
  }
};

REGISTER_BLOCK(readfile)

#endif //WORKFLOW__READFILE_H_
