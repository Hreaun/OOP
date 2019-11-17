#ifndef WORKFLOW__SORT_H_
#define WORKFLOW__SORT_H_

class sort : public iWorker {
 public:
  void execute(std::list<std::string> arg, std::list<std::string> &text) override {
    if (arg.size() != 1) {
      throw std::logic_error("sort doesn't require arguments.");
    }
    for (auto i = text.begin(); i != text.end(); i++) {
     if (std::all_of(i->begin(), i->end(), isspace)){
       text.erase(i);
     }
    }
    text.sort();
  }
};

REGISTER_BLOCK(sort)

#endif //WORKFLOW__SORT_H_
