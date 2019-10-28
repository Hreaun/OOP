#ifndef WORKFLOW__BLOCKFACTORY_H_
#define WORKFLOW__BLOCKFACTORY_H_
#include "iWorker.h"

class iBlockCreator {
 public:
  [[nodiscard]] virtual iWorker *create() const = 0;
};

template<class C>
class blockCreator : public iBlockCreator {
 public:
  [[nodiscard]] iWorker *create() const override { return new C(); }
};

class blockFactory {
 protected:
  typedef std::map<std::string, iBlockCreator *> FactoryMap;
  FactoryMap factory;

 public:
  blockFactory() = default;
  ~blockFactory() = default;

  template<class C>
  void add(const std::string &id) {
    auto it = factory.find(id);
    if (it == factory.end())
      factory[id] = new blockCreator<C>();
  }

  iWorker *create(const std::string &id) {
    auto it = factory.find(id);
    if (it != factory.end())
      return it->second->create();
    return nullptr;
  }
};

#endif //WORKFLOW__BLOCKFACTORY_H_