#ifndef WORKFLOW__IWORKER_H_
#define WORKFLOW__IWORKER_H_

#include <list>
class iWorker {
 public:
  virtual void execute(std::list<std::string> arg, std::list<std::string> &text) = 0;
  iWorker() = default;
  virtual ~iWorker() = default;
};

#endif //WORKFLOW__IWORKER_H_