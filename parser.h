#ifndef WORKFLOW__PARSER_H_
#define WORKFLOW__PARSER_H_

#include <map>
#include <string>
#include <stdexcept>
#include <list>
#include <fstream>
#include "iParser.h"

class parser : public iParser {
 private:
  std::map<int, std::list<std::string>> scheme;
  std::list<int> sequence;

 public:
  void parse(std::ifstream &in) override;

  [[nodiscard]] const std::map<int, std::list<std::string>> &getScheme() const {
    return scheme;
  }
  [[nodiscard]] const std::list<int> &getSequence() const {
    return sequence;
  }
};

void parser::parse(std::ifstream &in) {
  std::string str;
  getline(in, str);
  if (str != "desc") {
    throw std::logic_error("Invalid format.");
  }
  std::string id;
  while (!in.eof()) {
    in >> id;
    if (id == "csed") {
      break;
    }
    if (!scheme[stoi(id)].empty()) {
      throw std::logic_error("Found repeated command number");
    }
    in >> str;
    if (str != "=")
      throw std::logic_error("Invalid format.\n Put \"=\" after a command number.");
    do {
      in >> str;
      scheme[stoi(id)].push_back(str);
    } while ((in.get() != '\n') && (!in.eof()));
  }
  if (id != "csed") {
    throw std::logic_error("Wrong file content");
  }
  do {
    in >> str;
    if (str != "->") {
      sequence.push_back(stoi(str));
    }
  } while (in.get() != '\n' && !in.eof());
}

#endif //WORKFLOW__PARSER_H_