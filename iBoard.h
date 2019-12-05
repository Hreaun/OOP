#ifndef THEGAME__IBOARD_H_
#define THEGAME__IBOARD_H_

#include "iShip.h"
#pragma once
class iBoard {
 public:
  virtual auto getBoard() -> std::vector<std::string> = 0;
  iBoard() = default;
  ~iBoard() = default;
};

void clearScreen() {
  for (auto n = 0; n < 10; n++)
    printf("\n\n\n\n\n\n\n\n\n\n");
}

#endif //THEGAME__IBOARD_H_
