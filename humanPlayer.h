#ifndef THEGAME__HUMANPLAYER_H_
#define THEGAME__HUMANPLAYER_H_

#include "iPlayer.h"
#pragma once
class humanPlayer : public iPlayer {
 public:
  void shipSet() override;
  void play(iPlayer &enemy, std::string player) override;
  void deadLabel(iPlayer &enemy, int x, int y) override;
  void showBoards();
  ~humanPlayer() {
    for (auto &row : this->curPlBoard.table) {
      for (auto &col : row)
        delete col;
    }
  }
};

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

bool enoughSpace(bool (&allowed)[10][10], unsigned char orient, int x, int y, int size) {
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

void humanPlayer::shipSet() {
  std::vector<std::string> board = this->curPlBoard.getBoard();

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
    std::cout << "You have:\n";
    for (auto i = 0; i < 4; ++i){
      std::cout << i + 1 << "-decker(s): " << shipCount[i] << std::endl;
    }

    board = this->curPlBoard.getBoard();
    for (auto &i : board) {
      std::cout << i;
    }

    std::cout << "Enter size of a ship: ";
    std::cin >> size;
    if ((size > 4) || (size < 1)) {
      std::cout << "Wrong size\n";
      continue;
    }

    if (shipCount[size - 1] == 0) {
      std::cout << "You've used all ships of this type.\n";
      continue;
    }

    if (size > 1) {
      std::cout << "Enter orientation of a ship: ";
      std::cin >> orientation;
    }
    orientation = toupper(orientation);
    if ((orientation != 'V') && (orientation != 'H')) {
      std::cout << "Wrong orientation.\n";
      continue;
    }

    std::cout << "Enter X coordinate of a ship (A - J): ";
    std::cin >> x;
    x = toupper(x);
    if ((x > 'J') || (x < 'A')) {
      std::cout << "Wrong X coordinate.\n";
      continue;
    }

    std::cout << "Enter Y coordinate of a ship (0 - 9): ";
    std::cin >> y;
    if ((y > 9) || (y < 0)) {
      std::cout << "Wrong Y coordinate.\n";
      continue;
    }

    if (enoughSpace(allowed, orientation, x - 'A', y, size)) {
      if (size == 1)
        this->curPlBoard.table[y][x - 'A'] = new ship(size, orientation, x - 'A', y);
      else {
        this->curPlBoard.table[y][x - 'A'] = new ship(size, orientation, x - 'A', y);
        if (orientation == 'V') {
          for (auto i = 1; i < size; ++i)
            this->curPlBoard.table[y - i][x - 'A'] = this->curPlBoard.table[y][x - 'A'];
        } else {
          for (auto i = 1; i < size; ++i)
            this->curPlBoard.table[y][x - 'A' + i] = this->curPlBoard.table[y][x - 'A'];
        }
      }
    } else {
      std::cout << "You cannot set a ship here." << std::endl;
      continue;
    }
    shipCount[size - 1]--;
    busy(allowed, orientation, x - 'A', y, size);
    ++count;
  }
}

void humanPlayer::showBoards() {
  std::vector<std::string> left = this->enmBoard.getBoard();
  std::vector<std::string> right = this->curPlBoard.getBoard();
  for (auto i = 0; i < left.size(); ++i) {
    std::cout << left[i] + right[i];
  }
}

void humanPlayer::deadLabel(iPlayer &enemy, int x, int y) {
  if (enemy.curPlBoard.table[y][x]->orientation == 'V') {
    size_t tailOfShip = enemy.curPlBoard.table[y][x]->y - enemy.curPlBoard.table[y][x]->shipParts.size();
    for (size_t i = enemy.curPlBoard.table[y][x]->y; i > tailOfShip; --i)
      this->enmBoard.table[i][x] = 'X';
  } else {
    size_t tailOfShip = enemy.curPlBoard.table[y][x]->x + enemy.curPlBoard.table[y][x]->shipParts.size();
    for (size_t i = enemy.curPlBoard.table[y][x]->x; i < tailOfShip; ++i)
      this->enmBoard.table[y][i] = 'X';
  }
}

void humanPlayer::play(iPlayer &enemy, std::string player) {
  if (this->shipAmount == 0)
    return;

  bool hit = true;
  char x = 0;
  int y = 0;

  while (hit) {
    std::cout << "Player " << player << " turn\n";
    showBoards();
    if (enemy.shipAmount == 0) {
      std::cout << "Player " << player << " won!\n";
      return;
    }
    std::cout << "Enter X coordinate to hit (A - J): ";
    std::cin >> x;
    x = toupper(x);
    if ((x > 'J') || (x < 'A')) {
      std::cout << "Wrong X coordinate.\n";
      continue;
    }

    std::cout << "Enter Y coordinate to hit (0 - 9): ";
    std::cin >> y;
    if ((y > 9) || (y < 0)) {
      std::cout << "Wrong Y coordinate.\n";
      continue;
    }

    if (enemy.curPlBoard.table[y][x - 'A'] == nullptr) {
      std::cout << "You missed.\n";
      this->enmBoard.table[y][x - 'A'] = 'M';
      hit = false;
    } else {
      if (enemy.curPlBoard.table[y][x - 'A']->damaged) {
        if (enemy.curPlBoard.table[y][x - 'A']->partDamaged(x - 'A', y)) {
          std::cout << "You already hit this point.\n";
          continue;
        }
      }

      this->enmBoard.table[y][x - 'A'] = 'H';
      enemy.curPlBoard.table[y][x - 'A']->damaged = true;
      enemy.curPlBoard.table[y][x - 'A']->takeDamage(x - 'A', y);
      if (enemy.curPlBoard.table[y][x - 'A']->isSunken()) {
        enemy.shipAmount--;
        deadLabel(enemy, x - 'A', y);
      }
    }
  }
}

#endif //THEGAME__HUMANPLAYER_H_
