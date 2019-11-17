#ifndef WORKFLOW__WRITEFILE_H_
#define WORKFLOW__WRITEFILE_H_

class writefile : public iWorker {
 public:
  void execute(std::list<std::string> arg, std::list<std::string> &text) override {
    if (arg.size() != 2) {
      throw std::logic_error("writefile requires 1 argument.");
    }
    std::ofstream out;
    out.open(arg.back());
    for (std::string const &i : text) {
      out << i;
      out << std::endl;
    }
    out.close();
  }
};

REGISTER_BLOCK(writefile)

#endif //WORKFLOW__WRITEFILE_H_