#ifndef WORKFLOW__REPLACE_H_
#define WORKFLOW__REPLACE_H_

class replace : public iWorker {
 public:
  void execute(std::list<std::string> arg, std::list<std::string> &text) override {
    if (arg.size() != 3) {
      throw std::logic_error("replace requires 2 argument.");
    }
    std::string secondWord = arg.back();
    arg.pop_back();
    std::string firstWord = arg.back();
    size_t index = 0;
    for (auto & i : text) {
      index = 0;
      while (true) {
        index = i.find(firstWord, index);
        if (index == std::string::npos) break;
        i.replace(i.find(firstWord), firstWord.length(), secondWord);
        index += secondWord.length();
      }
    }
  }
};

REGISTER_BLOCK(replace)

#endif //WORKFLOW__REPLACE_H_
