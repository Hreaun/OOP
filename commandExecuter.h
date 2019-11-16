#ifndef WORKFLOW__COMMANDEXECUTER_CPP_
#define WORKFLOW__COMMANDEXECUTER_CPP_
#include "blockFactory.h"
#include "readfile.h"
#include "writefile.h"
#include "grep.h"
#include "dump.h"
#include "replace.h"
#include "sort.h"

void commandExecuter() {
  if (parser::scheme[parser::sequence.back()].front() != "writefile") // if last command != writefile
    throw std::logic_error("Wrong sequence format");
  for (auto const &k : parser::sequence) {
    if ((k != parser::sequence.back()) & (parser::scheme[k].front() == "writefile"))
      throw std::logic_error("Wrong sequence format");
    if ((k == parser::sequence.front()) & (parser::scheme[k].front() != "readfile"))
      throw std::logic_error("Wrong sequence format");
    iWorker *p = blockFactory::instance().create(parser::scheme[k].front());
    p->execute(parser::scheme[k]);
    delete p;
  }
}

#endif //WORKFLOW__COMMANDEXECUTER_CPP_
