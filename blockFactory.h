#ifndef WORKFLOW__BLOCKFACTORY_H_
#define WORKFLOW__BLOCKFACTORY_H_

#include "parser.h"
#include "iWorker.h"

#define REGISTER_BLOCK(T) static blockCreator<T> T(#T);

class iBlockCreator {
 public:
  [[nodiscard]] virtual iWorker *create() const = 0;
};

class blockFactory {
 protected:
  std::map<std::string, iBlockCreator *> mapOfBlocks;

 public:
  static blockFactory &instance();

 private:
  blockFactory() = default;
  ~blockFactory() = default;

 public:
  blockFactory(blockFactory const &) = delete;
  blockFactory &operator=(blockFactory const &) = delete;

  void registerMaker(const std::string &key, iBlockCreator *maker) {
    if (mapOfBlocks.find(key) != mapOfBlocks.end()) {
      throw std::logic_error("Multiple makers for given key!");
    }
    mapOfBlocks[key] = maker;
  }

  iWorker *create(const std::string &id) {
    auto it = mapOfBlocks.find(id);
    if (it != mapOfBlocks.end()) {
      return it->second->create();
    }
    return nullptr;
  }
};

template<typename T>
class blockCreator : public iBlockCreator {
 public:
  [[nodiscard]] iWorker *create() const override { return new T(); }
  explicit blockCreator(const std::string &key) {
    blockFactory::instance().registerMaker(key, this);
  }
};

blockFactory &blockFactory::instance() {
  static blockFactory factory;
  return factory;
}

#endif //WORKFLOW__BLOCKFACTORY_H_