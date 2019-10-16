#include "tritset.h"

int main() {
  tritset a(9);
  tritset b(100);
  a[0] = trit::False;
  b[90] = trit::False;
  a[2] = trit::True;
  a[1] = a[2];
  tritset c = a & b;
  std::cout << a[1] << std::endl;

  return 0;
}