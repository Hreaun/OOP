#ifndef THEGAME__ISHIP_H_
#define THEGAME__ISHIP_H_

#include <string>
#include <vector>
#pragma once

#define DAMAGED true

class iShip {
  friend class humanPlayer;
  friend class randomPlayer;
  friend class smartPlayer;
 public:
  virtual auto isSunken() -> bool = 0;
  virtual auto partDamaged(int x, int y) -> bool = 0;
  virtual void takeDamage(int x, int y) = 0;
  iShip() = default;
  virtual ~iShip() = default;
 protected:
  bool damaged = false;
  std::vector<bool> shipParts;
  unsigned char orientation{};
  int x{};
  int y{};
};

class ship : public iShip {
 public:
  auto isSunken() -> bool override;
  auto partDamaged(int x, int y) -> bool override;
  void takeDamage(int x, int y) override;
  ship(int size, unsigned char orientation, int x, int y) {
    this->shipParts.assign(size, false);
    this->orientation = orientation;
    this->x = x;
    this->y = y;
  }
};

auto ship::partDamaged(int x, int y) -> bool {
  if (orientation == 'V') {
    if (shipParts[this->y - y])
      return true;
  } else {
    if (shipParts[x - this->x])
      return true;
  }
  return false;
}

void ship::takeDamage(int x, int y) {
  if (orientation == 'V') {
    shipParts[this->y - y] = DAMAGED;
  } else {
    shipParts[x - this->x] = DAMAGED;
  }
}

auto ship::isSunken() -> bool {
  int sunkCounter = 0;
  for (auto i : shipParts) {
    if (i == DAMAGED)
      sunkCounter++;
  }
  return sunkCounter == shipParts.size();
}

#endif //THEGAME__ISHIP_H_
