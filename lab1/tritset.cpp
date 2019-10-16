#include "tritset.h"

tritset::tritset(size_t size) {
  sizeInTrits = size;
  sizeInChars = (size % 4 == 0) ? size / 4 : size / 4 + 1;
  container.resize(sizeInChars);
}

tritset::reference tritset::operator[](size_t position) {
  if (position >= sizeInTrits)
    return tritset::reference(position);
  return tritset::reference(container[position / 4], position % 4);
}

trit tritset::operator[](size_t position) const {
  if (position >= sizeInTrits)
    return trit::Unknown;
  return (trit) ((container[position / 4] & (mask << (6 - 2 * (position % 4))))
      >> (6 - 2 * (position % 4))); //доступ к (6 - 2 * position % 4)-му триту
}

tritset::reference::reference(unsigned char &oneChar, size_t position) : pos(position) {
  pOneChar = &oneChar;
}

tritset::reference::reference(size_t pos) : pos(pos) {
  pOneChar = nullptr;
}

tritset::reference::operator trit() {
  return this->getTrit();
}

tritset::reference &tritset::reference::operator=(trit x) {
  *pOneChar = (*pOneChar & ~(mask << (6 - 2 * (pos % 4))));
  *pOneChar = *pOneChar | ((unsigned) x << (6 - 2 * (pos % 4)));
  return *this;
}

tritset::reference &tritset::reference::operator=(const tritset::reference reference) {
  if (pOneChar == nullptr)
    if ((reference.getTrit() == trit::True) || (reference.getTrit() == trit::False)){

    }

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
  if (pOneChar == nullptr)
    return trit::Unknown;
  return (trit) ((*pOneChar & (tritset::mask << (6 - 2 * (pos % 4)))) >> (6 - 2 * (pos % 4)));
}

tritset operator&(tritset& a, tritset&b){
  size_t size = (a.sizeInTrits >= b.sizeInTrits) ? a.sizeInTrits : b.sizeInTrits;
  tritset c(size);
  for(size_t i = 0; i < size; ++i){
    c[i] = a[i] & b[i];
  }
  return c;
}

tritset operator|(tritset& a, tritset&b){
  size_t size = (a.sizeInTrits >= b.sizeInTrits) ? a.sizeInTrits : b.sizeInTrits;
  tritset c(size);
  for(size_t i = 0; i < size; ++i){
    c[i] = a[i] | b[i];
  }
  return c;
}

size_t tritset::getSize() {
  return this->sizeInTrits;
}

