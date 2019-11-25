#ifndef WORKFLOW__GREP_H_
#define WORKFLOW__GREP_H_

class grep : public iWorker {
 public:
  void execute(std::list<std::string> arg, std::list<std::string> &text) override {
    if (arg.size() != 2) {
      throw std::logic_error("grep requires 1 argument.");
    }
    std::string givenWord = arg.back();
    auto it = text.begin();
    auto last = it;
    while(it != text.end()){
      last = it;
      it++;
      if (last->find(givenWord) == std::string::npos) {
        text.erase(last);
      }
    }
  }
};

REGISTER_BLOCK(grep)

#endif //WORKFLOW__GREP_H_
