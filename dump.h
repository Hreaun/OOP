#ifndef WORKFLOW__DUMP_H_
#define WORKFLOW__DUMP_H_

#include "readfile.h"

class dump : public readfile{
 public:
  void execute(std::list<std::string> arg) override {
   writefile a;
   a.execute(arg);
  }
};

#endif //WORKFLOW__DUMP_H_
