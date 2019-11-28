#ifndef WORKFLOW__DUMP_H_
#define WORKFLOW__DUMP_H_

#include "writefile.h"

class dump : public iWorker {
 public:
    workerType getType() override {
        return workerType::INOUT;
    }

  void execute(std::list<std::string> arg, std::list<std::string> &text) override {
      if (arg.size() != 2) {
          throw std::logic_error("dump requires 1 argument.");
      }
      std::ofstream out;
      out.open(arg.back());
      for (std::string const &i : text) {
          out << i;
          out << std::endl;
      }
      out.close();
  }
};

REGISTER_BLOCK(dump)

#endif //WORKFLOW__DUMP_H_
