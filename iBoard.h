#ifndef THEGAME__IBOARD_H_
#define THEGAME__IBOARD_H_

#include "iShip.h"
#pragma once
class iBoard {
 public:
  virtual std::vector<std::string> getBoard() = 0;
  iBoard() = default;
  ~iBoard() = default;

};

#endif //THEGAME__IBOARD_H_
