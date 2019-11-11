#ifndef WORKFLOW__WRITEFILE_H_
#define WORKFLOW__WRITEFILE_H_

#include "readfile.h"

class writefile : public readfile {
 public:
  void execute(std::list<std::string> arg) override {
    std::ofstream out;
    out.open(arg.back());
    for (std::string const &i : text) {
      out << i;
      out << std::endl;
    }
    out.close();
  }
};

REGISTER_BLOCK(writefile)

#endif //WORKFLOW__WRITEFILE_H_