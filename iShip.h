#ifndef THEGAME__ISHIP_H_
#define THEGAME__ISHIP_H_

#include <string>
#include <vector>
#pragma once

#define DAMAGED true

class iShip {
  friend class humanPlayer;
  friend class randomPlayer;
 public:
  virtual bool isSunken() = 0;
  virtual bool partDamaged(int x, int y) = 0;
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
  bool isSunken() override;
  bool partDamaged(int x, int y) override;
  void takeDamage(int x, int y) override;
  ship(int size, unsigned char orientation, int x, int y) {
    this->shipParts.assign(size, false);
    this->orientation = orientation;
    this->x = x;
    this->y = y;
  }
};

bool ship::partDamaged(int x, int y) {
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

bool ship::isSunken() {
  int sunkCounter = 0;
  for (auto i : shipParts) {
    if (i == DAMAGED)
      sunkCounter++;
  }
  return sunkCounter == shipParts.size();
}

#endif //THEGAME__ISHIP_H_
