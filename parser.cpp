#include "parser.h"
#include "blockFactory.h"
#include "readfile.h"
#include "writefile.h"
#include "grep.h"
#include "sort.h"
#include "replace.h"
#include "dump.h"

parser::parser(std::ifstream &in) {
  std::string str;
  getline(in, str);
  if (str != "desc") {
    throw std::logic_error("Invalid format");
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
      throw std::logic_error("Invalid format");
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
  commandExecuter();
}

void parser::commandExecuter() {
  blockFactory factory;
  factory.add<writefile>("writefile");
  factory.add<readfile>("readfile");
  factory.add<grep>("grep");
  factory.add<sort>("sort");
  factory.add<replace>("replace");
  factory.add<dump>("dump");
  for (auto const& k : sequence){
    if ((k != sequence.back()) & (scheme[k].front() == "writefile"))
      throw std::logic_error("Wrong format");
    if ((k == sequence.front()) & (scheme[k].front() != "readfile"))
      throw std::logic_error("Wrong format");
    iWorker *p = factory.create(scheme[k].front());
    p->execute(scheme[k]);
  }
}