#ifndef WORKFLOW__PARSER_H_
#define WORKFLOW__PARSER_H_

#include <map>
#include <string>
#include <stdexcept>
#include <list>
#include <fstream>

class parser {
 private:
  std::map<int, std::list<std::string>> scheme;
  std::list<int> sequence;

 public:
  void commandExecuter();
  explicit parser(std::ifstream &in);
};

#endif //WORKFLOW__PARSER_H_