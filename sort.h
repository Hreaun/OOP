#ifndef WORKFLOW__SORT_H_
#define WORKFLOW__SORT_H_
#include "readfile.h"
class sort : public readfile{
 public:
  void execute(std::list<std::string> arg) override {
    for (auto i = text.begin(); i != text.end(); i++) {
     if (std::all_of(i->begin(), i->end(), isspace)){
       text.erase(i);
     }
    }
    text.sort();
  }
};

REGISTER_BLOCK(sort)

#endif //WORKFLOW__SORT_H_
