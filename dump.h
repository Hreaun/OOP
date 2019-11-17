#ifndef WORKFLOW__DUMP_H_
#define WORKFLOW__DUMP_H_

#include "writefile.h"

class dump : public iWorker {
 public:
  void execute(std::list<std::string> arg, std::list<std::string> &text) override {
    if (arg.size() != 2) {
      throw std::logic_error("dump requires 1 argument.");
    }
    class writefile a;
    a.execute(arg, text);
  }
};

REGISTER_BLOCK(dump)

#endif //WORKFLOW__DUMP_H_
