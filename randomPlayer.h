#ifndef THEGAME__RANDOMPLAYER_H_
#define THEGAME__RANDOMPLAYER_H_

#include "iPlayer.h"
#include <random>
#include <iostream>

#pragma once
class randomPlayer : public iPlayer {
  void play(iPlayer &enemy, std::string player) override;
  void deadLabel(iPlayer &enemy, int x, int y) override;
  void shipSet() override;
 public:
  ~randomPlayer() override {
    for (auto &i : this->ships) {
      delete i;
    }
  }
};

void randomPlayer::deadLabel(iPlayer &enemy, int x, int y) {
  if (enemy.curPlBoard.table[y][x]->orientation == 'V') {
    int tailOfShip = (enemy.curPlBoard.table[y][x]->y + 1) - enemy.curPlBoard.table[y][x]->shipParts.size();
    for (int i = enemy.curPlBoard.table[y][x]->y; i >= tailOfShip; --i)
      this->enmBoard.table[i][x] = 'X';
  } else {
    int tailOfShip = enemy.curPlBoard.table[y][x]->x + enemy.curPlBoard.table[y][x]->shipParts.size();
    for (int i = enemy.curPlBoard.table[y][x]->x; i < tailOfShip; ++i)
      this->enmBoard.table[y][i] = 'X';
  }
}

void randomPlayer::shipSet() {
  std::random_device r;
  std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
  std::mt19937 eng{seed};
  std::uniform_int_distribution<> dist(0, 9);
  std::uniform_int_distribution<> shipSize(1, 4);

  bool allowed[10][10];
  for (auto &row : allowed) {
    for (auto &col : row) {
      col = true;
    }
  }

  int size = 0;
  unsigned char orientation = 'V';
  char x = 0;
  int y = 0;
  int shipCount[] = {4, 3, 2, 1}; //{4, 3, 2, 1} // 4 корабля 1 размера и т.д.
  int shipAmount = 0;
  for (auto &i : shipCount) {
    shipAmount += i;
  }

  this->shipAmount = shipAmount;

  for (auto count = 0; count < shipAmount;) {
    size = shipSize(eng);

    if (shipCount[size - 1] == 0) {
      continue;
    }

    if (size > 1) {
      if (dist(eng) / 2 == 0)
        orientation = 'V';
      else
        orientation = 'H';
    }

    x = dist(eng);
    y = dist(eng);

    if (enoughSpace(allowed, orientation, x, y, size)) {
      if (size == 1) {
        this->curPlBoard.table[y][x] = new ship(size, orientation, x, y);
        this->ships[count] = this->curPlBoard.table[y][x];
      } else {
        this->curPlBoard.table[y][x] = new ship(size, orientation, x, y);
        this->ships[count] = this->curPlBoard.table[y][x];
        if (orientation == 'V') {
          for (auto i = 1; i < size; ++i)
            this->curPlBoard.table[y - i][x] = this->curPlBoard.table[y][x];
        } else {
          for (auto i = 1; i < size; ++i)
            this->curPlBoard.table[y][x + i] = this->curPlBoard.table[y][x];
        }
      }
    } else {
      continue;
    }
    shipCount[size - 1]--;
    busy(allowed, orientation, x, y, size);
    ++count;
  }
}

void randomPlayer::play(iPlayer &enemy, std::string player) {
  std::random_device r;
  std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
  std::mt19937 eng{seed};
  std::uniform_int_distribution<> dist(0, 9);

  if (this->shipAmount == 0)
    return;

  bool hit = true;
  char x = 0;
  int y = 0;
  std::cout << player << " player " << " turn\n";

  while (hit) {
    if (enemy.shipAmount == 0) {
      std::cout << player << " player " << " won!\n";
      return;
    }
    x = dist(eng);
    y = dist(eng);

    if (this->enmBoard.table[y][x] != '+') {
      continue;
    } else if (enemy.curPlBoard.table[y][x] == nullptr) {
      this->enmBoard.table[y][x] = 'M';
      hit = false;
      continue;
    }
    this->enmBoard.table[y][x] = 'H';
    enemy.curPlBoard.table[y][x]->damaged = true;
    enemy.curPlBoard.table[y][x]->takeDamage(x, y);
    if (enemy.curPlBoard.table[y][x]->isSunken()) {
      enemy.shipAmount--;
      deadLabel(enemy, x, y);
    }
  }
}


#endif //THEGAME__RANDOMPLAYER_H_
