#ifndef THEGAME__IPLAYER_H_
#define THEGAME__IPLAYER_H_
#include "curPlayerBoard.h"
#include "enemyBoard.h"
#pragma once

class iPlayer {
 public:
  iPlayer() = default;
  virtual ~iPlayer() = default;
  curPlayerBoard curPlBoard;
  enemyBoard enmBoard;
  iShip *ships[10]{nullptr};
  int shipAmount{};

  virtual void play(iPlayer &enemy, std::string player) = 0;
  virtual void shipSet() = 0;
  virtual void deadLabel(iPlayer &enemy, int x, int y) = 0;
};

auto enoughSpace(bool (&allowed)[10][10], unsigned char orient, int x, int y, int size) -> bool {
  if (orient == 'V') {
    if (((y + 1) - size) < 0)
      return false;
    for (auto j = size - 1; j >= 0; --j) {
      if (!allowed[y - j][x])
        return false;
    }
  } else {
    if (((x - 1) + size) > 9)
      return false;
    for (auto i = 0; i < size; ++i) {
      if (!allowed[y][x + i])
        return false;
    }
  }
  return true;
}

void busy(bool (&allowed)[10][10], unsigned char orient, int x, int y, int size) { // пространство, занимаемое кораблем.
  if (orient == 'V') {                                                             // площадь 3*(размер корабля + 2)
    y++;                                                                           // вокруг него
    x--;
    for (auto i = 0; i < 3; ++i) {
      for (auto j = size + 1; j >= 0; --j) {
        if (((x + i) >= 0) && ((x + i) <= 9) && ((y - j) >= 0) && ((y - j) <= 9))
          allowed[y - j][x + i] = false;
      }
    }
  } else {
    x--;
    y++;
    for (auto i = 0; i < size + 2; ++i) {
      for (auto j = 2; j >= 0; --j) {
        if (((x + i) >= 0) && ((x + i) <= 9) && ((y - j) >= 0) && ((y - j) <= 9))
          allowed[y - j][x + i] = false;
      }
    }
  }
}

#endif //THEGAME__IPLAYER_H_
