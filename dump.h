#ifndef WORKFLOW__DUMP_H_
#define WORKFLOW__DUMP_H_

#include "readfile.h"
#include "writefile.h"


class dump : public readfile{
 public:
  void execute(std::list<std::string> arg) override {
    class writefile a;
   a.execute(arg);
  }
};

REGISTER_BLOCK(dump)

#endif //WORKFLOW__DUMP_H_
