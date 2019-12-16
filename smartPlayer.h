#ifndef THEGAME__SMARTPLAYER_H_
#define THEGAME__SMARTPLAYER_H_

#include <random>
#include <iostream>
#include "iPlayer.h"
class smartPlayer : public iPlayer {
  char lastHit[2]{};
  unsigned char direction{0};
  char firstHit[2]{};
  int hitCount{};
  void play(iPlayer &enemy, std::string player) override;
  void deadLabel(iPlayer &enemy, int x, int y) override;
  void shipSet() override;
  void showBoards();
 public:
  ~smartPlayer() override {
    for (auto &i : this->ships) {
      delete i;
    }
  }
};

void smartPlayer::showBoards() {
  std::vector<std::string> left = this->enmBoard.getBoard();
  std::vector<std::string> right = this->curPlBoard.getBoard();
  for (auto i = 0; i < left.size(); ++i) {
    std::cout << left[i] + right[i];
  }
}

auto rightPlace(bool (&allowed)[10][10], unsigned char orientation, int x, int y, int size) -> bool {
  int cellCount = 0;
  if (orientation == 'V') { // корабль не занимает больше 3*size клеток
    y++;
    x--;
    for (auto i = 0; i < 3; ++i) {
      for (auto j = size + 1; j >= 0; --j) {
        if (((x + i) >= 0) && ((x + i) <= 9) && ((y - j) >= 0) && ((y - j) <= 9) && allowed[y - j][x + i])
          cellCount++;
      }
    }
  } else {
    x--;
    y++;
    for (auto i = 0; i < size + 2; ++i) {
      for (auto j = 2; j >= 0; --j) {
        if (((x + i) >= 0) && ((x + i) <= 9) && ((y - j) >= 0) && ((y - j) <= 9) && allowed[y - j][x + i])
          cellCount++;
      }
    }
  }
  return (cellCount <= size * 3);
}

void smartPlayer::shipSet() {
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

    if (size != 1) {
      while (!rightPlace(allowed, orientation, x, y, size)) {
        x = dist(eng);
        y = dist(eng);
        if (dist(eng) / 2 == 0)
          orientation = 'V';
        else
          orientation = 'H';
      }
    }

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
    busy(allowed, orientation, x, y, size);
    shipCount[size - 1]--;
    ++count;
  }
}

void smartPlayer::deadLabel(iPlayer &enemy, int x, int y) {
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

void smartPlayer::play(iPlayer &enemy, std::string player) {
  std::random_device r;
  std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
  std::mt19937 eng{seed};
  std::uniform_int_distribution<> dist(0, 9);
  std::uniform_int_distribution<> dir(0, 3);

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

    if (this->hitCount > 0) {
      switch (this->direction) {
        case 0: {
          if ((this->lastHit[0] - 1) < 0) {
            this->direction = 1;
            this->lastHit[0] = this->firstHit[0];
            this->lastHit[1] = this->firstHit[1];
            continue;
          }
          x = this->lastHit[0] - 1;
          y = this->lastHit[1];
          break;
        }
        case 1: {
          if ((this->lastHit[0] + 1) > 9) {
            this->direction = 0;
            this->lastHit[0] = this->firstHit[0];
            this->lastHit[1] = this->firstHit[1];
            continue;
          }
          x = this->lastHit[0] + 1;
          y = this->lastHit[1];
          break;
        }
        case 2: {
          if ((this->lastHit[1] - 1) < 0) {
            this->direction = 3;
            this->lastHit[0] = this->firstHit[0];
            this->lastHit[1] = this->firstHit[1];
            continue;
          }
          x = this->lastHit[0];
          y = this->lastHit[1] - 1;
          break;
        }
        case 3: {
          if ((this->lastHit[1] + 1) > 9) {
            this->direction = 2;
            this->lastHit[0] = this->firstHit[0];
            this->lastHit[1] = this->firstHit[1];
            continue;
          }
          x = this->lastHit[0];
          y = this->lastHit[1] + 1;
          break;
        }
        default:;
      }
    } else {
      x = dist(eng);
      y = dist(eng);
    }

    if (this->enmBoard.table[y][x] != '+') {
      this->direction = dir(eng);
      if (this->hitCount > 0) {
        this->lastHit[0] = this->firstHit[0];
        this->lastHit[1] = this->firstHit[1];
      }
      continue;
    } else if (enemy.curPlBoard.table[y][x] == nullptr) {
      if (this->hitCount <= 1) {
        this->direction = (this->direction + 1) % 4;
      } else {
        switch (this->direction) {
          case 0: {
            this->direction = 1;
            this->lastHit[0] = this->firstHit[0];
            this->lastHit[1] = this->firstHit[1];
            break;
          }
          case 1: {
            this->direction = 0;
            this->lastHit[0] = this->firstHit[0];
            this->lastHit[1] = this->firstHit[1];
            break;
          }
          case 2: {
            this->direction = 3;
            this->lastHit[0] = this->firstHit[0];
            this->lastHit[1] = this->firstHit[1];
            break;
          }
          case 3: {
            this->direction = 2;
            this->lastHit[0] = this->firstHit[0];
            this->lastHit[1] = this->firstHit[1];
            break;
          }
        }
      }
      this->enmBoard.table[y][x] = 'M';
      hit = false;
      continue;
    }

    this->enmBoard.table[y][x] = 'H';

    if (this->hitCount == 0) {
      this->firstHit[0] = x;
      this->firstHit[1] = y;
    }

    this->hitCount++;

    this->lastHit[0] = x;
    this->lastHit[1] = y;

    enemy.curPlBoard.table[y][x]->damaged = true;
    enemy.curPlBoard.table[y][x]->takeDamage(x, y);
    if (enemy.curPlBoard.table[y][x]->isSunken()) {
      this->hitCount = 0;
      enemy.shipAmount--;
      deadLabel(enemy, x, y);
    }
  }
}

#endif //THEGAME__SMARTPLAYER_H_
