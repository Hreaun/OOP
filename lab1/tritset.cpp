#include "tritset.h"

tritset::tritset(size_t size) {
  sizeInTrits = size;
  sizeInChars = (size % 4 == 0) ? size / 4 : size / 4 + 1;
  container.resize(sizeInChars);
}

tritset::reference tritset::operator[](size_t position) {
  return tritset::reference(*this, position);
}

trit tritset::operator[](size_t position) const {
  if (position >= sizeInTrits)
    return trit::Unknown;
  return (trit) ((container[position / 4] & (mask << (6 - 2 * (position % 4))))
      >> (6 - 2 * (position % 4))); //доступ к (6 - 2 * position % 4)-му триту
}

tritset::reference::reference(tritset &curTritset, size_t position) : pos(position) {
  this->pTritset = &curTritset;
}

tritset::reference::operator trit() {
  return this->getTrit();
}

tritset::reference &tritset::reference::operator=(trit x) {
  if (pTritset->sizeInTrits <= pos) {
    if (x == trit::Unknown) {
      return *this;
    } else {
      pTritset->sizeInChars = (pos % 4 == 0) ? pos / 4 : pos / 4 + 1;
      pTritset->container.resize(pTritset->sizeInChars);
      pTritset->sizeInTrits = pos + 1;
    }
  }
  pTritset->container[pos / 4] = (pTritset->container[pos / 4] & ~(mask << (6 - 2 * (pos % 4))));
  pTritset->container[pos / 4] = pTritset->container[pos / 4] | ((unsigned) x << (6 - 2 * (pos % 4)));
  return *this;
}

tritset::reference &tritset::reference::operator=(const tritset::reference reference) {
  *this = reference.getTrit();
  return *this;
}

std::ostream &operator<<(std::ostream &out, const tritset::reference a) {
  out << a.getTrit();
  return out;
}

std::istream &operator>>(std::istream &in, tritset::reference a) {
  trit input;
  in >> input;
  a.operator=(input);
  return in;
}

trit tritset::reference::getTrit() const {
  if (pTritset->sizeInTrits <= pos)
    return trit::Unknown;
  return (trit) ((pTritset->container[pos / 4] & (tritset::mask << (6 - 2 * (pos % 4))))
      >> (6 - 2 * (pos % 4)));
}

tritset operator&(tritset &a, tritset &b) {
  size_t size = (a.sizeInTrits >= b.sizeInTrits) ? a.sizeInTrits : b.sizeInTrits;
  tritset c(size);
  for (size_t i = 0; i < size; ++i) {
    c[i] = a[i] & b[i];
  }
  return c;
}

tritset operator|(tritset &a, tritset &b) {
  size_t size = (a.sizeInTrits >= b.sizeInTrits) ? a.sizeInTrits : b.sizeInTrits;
  tritset c(size);
  for (size_t i = 0; i < size; ++i) {
    c[i] = a[i] | b[i];
  }
  return c;
}

size_t tritset::getSize() {
  return this->sizeInTrits;
}

