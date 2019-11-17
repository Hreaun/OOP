#ifndef WORKFLOW__GREP_H_
#define WORKFLOW__GREP_H_

class grep : public iWorker {
 public:
  void execute(std::list<std::string> arg, std::list<std::string> &text) override {
    if (arg.size() != 2) {
      throw std::logic_error("grep requires 1 argument.");
    }
    std::string givenWord = arg.back();
    for (auto it = text.begin(); it != text.end(); it++) {
      if (it->find(givenWord) == std::string::npos){
        text.erase(it);
      }
    }
  }
};

REGISTER_BLOCK(grep)

#endif //WORKFLOW__GREP_H_