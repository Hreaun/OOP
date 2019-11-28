#ifndef WORKFLOW__IWORKER_H_
#define WORKFLOW__IWORKER_H_

#include <list>

enum class workerType {
    IN,
    OUT,
    INOUT,
};

class iWorker {
 public:
  virtual void execute(std::list<std::string> arg, std::list<std::string> &text) = 0;
  virtual workerType getType() = 0;

  virtual ~iWorker() = default;
};

#endif //WORKFLOW__IWORKER_H_
