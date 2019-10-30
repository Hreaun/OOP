#ifndef WORKFLOW__IWORKER_H_
#define WORKFLOW__IWORKER_H_
#include "parser.h"
#include <stdexcept>

class iWorker {
 public:
  virtual void execute(std::list <std::string> arg) = 0;
  iWorker() = default;
  virtual ~iWorker() = default;
};

#endif //WORKFLOW__IWORKER_H_