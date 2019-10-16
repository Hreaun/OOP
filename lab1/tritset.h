#ifndef TRITSET__TRITSET_H_
#define TRITSET__TRITSET_H_

#include <vector>
#include "trit.h"

class tritset {
 private:
  static const size_t mask = 0b11;
  size_t sizeInChars{};
  size_t sizeInTrits{};
  std::vector<unsigned char> container;

 public:

  tritset() { sizeInChars = 0; }

  explicit tritset(size_t size);

  class reference {
    friend class tritset;
    friend std::ostream &operator<<(std::ostream &out, tritset::reference a);
    friend std::istream &operator>>(std::istream &in, tritset::reference a);

    tritset* pTritset{};
    size_t pos{};

   protected:
    [[nodiscard]] trit getTrit() const;
   public:
    reference(tritset &curTritset, size_t position);

    operator trit(); // приведение типа
    reference &operator=(trit x);
    reference &operator=(reference reference);

  };

  friend class reference;
  friend tritset operator&(tritset& a, tritset&b);
  friend tritset operator|(tritset& a, tritset&b);
  reference operator[](size_t position);
  trit operator[](size_t position) const;
  size_t getSize();

};

#endif //TRITSET__TRITSET_H_
