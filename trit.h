#ifndef TRITSET__TRIT_H_
#define TRITSET__TRIT_H_

#include <iostream>

enum class trit { Unknown = 0, False, True };

trit operator&(const trit &a, const trit &b);

trit operator|(const trit &a, const trit &b);

trit operator~(const trit &a);

void operator|=(trit &a, trit b);

void operator&=(trit &a, trit b);

std::ostream &operator<<(std::ostream &out, trit a);

std::istream &operator>>(std::istream &in, trit &a);

#endif //TRITSET__TRIT_H_
