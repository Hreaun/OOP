#ifndef WORKFLOW__COMMANDEXECUTER_H_
#define WORKFLOW__COMMANDEXECUTER_H_
#include <memory>
#include "blockFactory.h"
#include "readfile.h"
#include "writefile.h"
#include "grep.h"
#include "dump.h"
#include "replace.h"
#include "sort.h"

class commandExecuter {
 public:
  static void exe(std::map<int, std::list<std::string>> scheme, std::list<int> sequence) {
    if (scheme[sequence.back()].front() != "writefile") // if last command != writefile
      throw std::logic_error("Wrong sequence format");
    std::list<std::string> text;
    for (auto const &k : sequence) {
      if ((k != sequence.back()) & (scheme[k].front() == "writefile"))
        throw std::logic_error("Wrong sequence format");
      if ((k == sequence.front()) & (scheme[k].front() != "readfile"))
        throw std::logic_error("Wrong sequence format");
      std::unique_ptr<iWorker> p (blockFactory::instance().create(scheme[k].front()));
      p->execute(scheme[k], text);
    }
  };
};

#endif //WORKFLOW__COMMANDEXECUTER_CPP_
