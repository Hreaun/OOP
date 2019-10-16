#include "trit.h"

trit operator&(const trit &a, const trit &b) {
  if ((a == trit::False) || (b == trit::False))
    return trit::False;
  switch (static_cast<int>(a) * static_cast<int>(b)) {
    case (0): {
      return trit::Unknown;
    }
    default: return trit::True;
  }
}

trit operator|(const trit &a, const trit &b) {
  if ((a == trit::True) || (b == trit::True))
    return trit::True;
  switch (static_cast<int>(a) + static_cast<int>(b)) {
    case (2): return trit::False;
    default: return trit::Unknown;
  }
}

trit operator~(const trit &a) {
  switch (static_cast<int>(a)) {
    case (0): return trit::Unknown;
    case (1): return trit::True;
    default: return trit::False;
  }
}

void operator|=(trit &a, trit b) {
  a = a | b;
}

void operator&=(trit &a, trit b) {
  a = a & b;
}

std::ostream &operator<<(std::ostream &out, const trit a) {
  switch (static_cast<int>(a)) {
    case (0): {
      out << "Unknown";
      break;
    }
    case (1): {
      out << "False";
      break;
    }
    default: out << "True";
  }
  return out;
}

std::istream &operator>>(std::istream &in, trit &a) {
  std::string input;
  in >> input;
  if (input == "False")
    a = trit::False;
  else if (input == "Unknown")
    a = trit::Unknown;
  else if (input == "True")
    a = trit::True;
  else {
    throw std::overflow_error("Invalid value");
  }
  return in;
}


