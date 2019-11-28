#ifndef WORKFLOW__COMMANDEXECUTER_H_
#define WORKFLOW__COMMANDEXECUTER_H_
#include <memory>
#include <vector>
#include "blockFactory.h"
#include "readfile.h"
#include "writefile.h"
#include "grep.h"
#include "dump.h"
#include "replace.h"
#include "sort.h"

class commandExecuter {
 public:
    void exe(std::map<int, std::list<std::string>> scheme, const std::list<int>& sequence) {
      std::vector<std::shared_ptr<iWorker>> p;
      for (auto const &k : sequence){
          p.push_back(static_cast<const std::shared_ptr<iWorker>>(blockFactory::instance().create(scheme[k].front())));
      }

      for (auto i = 0; i < p.size(); ++i){
          if ((i == 0) && (p[i]->getType() != workerType::IN)){
              throw std::logic_error("Wrong sequence format");
          }
          if ((i > 0) && (i < p.size() - 1) && (p[i]->getType() != workerType::INOUT)){
              throw std::logic_error("Wrong sequence format");
          }
          if ((i == p.size() - 1) && (p[i]->getType() != workerType::OUT)){
              throw std::logic_error("Wrong sequence format");
          }
      }

    std::list<std::string> text;
      auto i = 0;
      for (auto const &k : sequence){
          p[i]->execute(scheme[k], text);
          i++;
      }
  };
};

#endif //WORKFLOW__COMMANDEXECUTER_CPP_
