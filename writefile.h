//
// Created by admin on 28/10/2019.
//

#ifndef WORKFLOW__WRITEFILE_H_
#define WORKFLOW__WRITEFILE_H_

#include "readfile.h"
class writefile : public readfile {
  void execute(std::list <std::string> arg) override{
    std::ofstream out;
    out.open(arg.back());
    std::string str;
    for (std::string const& i : text) {
      out << i;
      out << std::endl;
    }
    out.close();
  }
};

#endif //WORKFLOW__WRITEFILE_H_