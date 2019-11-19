#ifndef WORKFLOW__IPARSER_H_
#define WORKFLOW__IPARSER_H_
#include <iostream>

class iParser {
 public:
  virtual void parse(std::ifstream &in) = 0;
  iParser() = default;
  ~iParser() = default;
};

#endif //WORKFLOW__IPARSER_H_
