#ifndef THEGAME__HUMANPLAYER_H_
#define THEGAME__HUMANPLAYER_H_

#include <memory>
#include "iPlayer.h"
#pragma once
class humanPlayer : public iPlayer {
 public:
  void shipSet() override;
  void play(iPlayer &enemy, std::string player) override;
  void deadLabel(iPlayer &enemy, int x, int y) override;
  void showBoards();
  ~humanPlayer() override{
    for(auto &i : this->ships){
      delete i;
    }
  }
};

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
    clearScreen();
    std::cout << "You have:\n";
    for (auto i = 0; i < 4; ++i) {
      std::cout << i + 1 << "-decker(s): " << shipCount[i] << std::endl;
    }

    board = this->curPlBoard.getBoard();
    for (auto &i : board) {
      std::cout << i;
    }

    std::cout << "Enter size of a ship: ";
    std::cin >> size;
    if ((std::cin.fail()) || ((size > 4) || (size < 1))) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Wrong size\n";
      std::cout << "Press enter to continue.\n";
      getchar();
      continue;
    }

    if (shipCount[size - 1] == 0) {
      std::cout << "You've used all ships of this type.\n";
      std::cout << "Press enter to continue.\n";
      getchar();
      getchar();
      continue;
    }

    if (size > 1) {
      std::cout << "Enter orientation of a ship (V/H): ";
      std::cin >> orientation;
    }
    orientation = toupper(orientation);
    if ((orientation != 'V') && (orientation != 'H')) {
      std::cout << "Wrong orientation.\n";
      std::cout << "Press enter to continue.\n";
      getchar();
      getchar();
      continue;
    }

    std::cout << "Enter X coordinate of a ship (A - J)";
    if ((size != 1) && (orientation == 'H')) {
      std::cout << "(Left coordinate of the ship): ";
    } else { std::cout << ": "; }
    std::cin >> x;
    x = toupper(x);
    if ((x > 'J') || (x < 'A')) {
      std::cout << "Wrong X coordinate.\n";
      std::cout << "Press enter to continue.\n";
      getchar();
      getchar();
      continue;
    }

    std::cout << "Enter Y coordinate of a ship (0 - 9)";
    if ((size != 1) && (orientation == 'V')) {
      std::cout << "(Bottom coordinate of the ship): ";
    } else { std::cout << ": "; }
    std::cin >> y;
    if ((std::cin.fail()) || ((y > 9) || (y < 0))) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Wrong Y coordinate.\n";
      std::cout << "Press enter to continue.\n";
      getchar();
      continue;
    }

    if (enoughSpace(allowed, orientation, x - 'A', y, size)) {
      if (size == 1) {
        this->curPlBoard.table[y][x - 'A'] = new ship(size, orientation, x - 'A', y);
        this->ships[count] = this->curPlBoard.table[y][x - 'A'];
      } else {
        this->curPlBoard.table[y][x - 'A'] = new ship(size, orientation, x - 'A', y);
        this->ships[count] = this->curPlBoard.table[y][x - 'A'];
        if (orientation == 'V') {
          for (auto i = 1; i < size; ++i)
            this->curPlBoard.table[y - i][x - 'A'] = this->curPlBoard.table[y][x - 'A'];
        } else {
          for (auto i = 1; i < size; ++i)
            this->curPlBoard.table[y][x - 'A' + i] = this->curPlBoard.table[y][x - 'A'];
        }
      }
    } else {
      std::cout << "You cannot set the ship here." << std::endl;
      std::cout << "Press enter to continue.\n";
      getchar();
      getchar();
      continue;
    }
    shipCount[size - 1]--;
    busy(allowed, orientation, x - 'A', y, size);
    ++count;
  }

  clearScreen();
  board = this->curPlBoard.getBoard();
  for (auto &i : board) {
    std::cout << i;
  }
  std::cout << "You set your ships. Press enter to continue.\n";
  getchar();
  getchar();
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
    int tailOfShip = (enemy.curPlBoard.table[y][x]->y + 1) - enemy.curPlBoard.table[y][x]->shipParts.size();
    for (int i = enemy.curPlBoard.table[y][x]->y; i >= tailOfShip; --i)
      this->enmBoard.table[i][x] = 'X';
  } else {
    int tailOfShip = enemy.curPlBoard.table[y][x]->x + enemy.curPlBoard.table[y][x]->shipParts.size();
    for (int i = enemy.curPlBoard.table[y][x]->x; i < tailOfShip; ++i)
      this->enmBoard.table[y][i] = 'X';
  }
}

void humanPlayer::play(iPlayer &enemy, std::string player) {
  if (this->shipAmount == 0)
    return;

  bool hit = true;
  char x = 0;
  int y = 0;
  std::cout << player << " player " << " turn\n";
  std::cout << "Press enter to continue.\n";
  getchar();
  clearScreen();

  while (hit) {
    clearScreen();
    std::cout << player << " player " << " turn\n";
    showBoards();
    if (enemy.shipAmount == 0) {
      std::cout << player << " player " << " won!\n";
      return;
    }
    std::cout << "Enter X coordinate to hit (A - J): ";
    std::cin >> x;
    x = toupper(x);
    if ((x > 'J') || (x < 'A')) {
      std::cout << "Wrong X coordinate.\n";
      std::cout << "Press enter to continue.\n";
      getchar();
      getchar();
      continue;
    }

    std::cout << "Enter Y coordinate to hit (0 - 9): ";
    std::cin >> y;
    if ((std::cin.fail()) || ((y > 9) || (y < 0))) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Wrong Y coordinate.\n";
      std::cout << "Press enter to continue.\n";
      getchar();
      continue;
    }

    if (this->enmBoard.table[y][x - 'A'] != '+') {
      std::cout << "You already hit this point.\n";
      std::cout << "Press enter to continue.\n";
      getchar();
      getchar();
      continue;
    } else if (enemy.curPlBoard.table[y][x - 'A'] == nullptr) {
      this->enmBoard.table[y][x - 'A'] = 'M';
      hit = false;
      clearScreen();
      std::cout << "You missed.\n";
      getchar();
      continue;
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

#endif //THEGAME__HUMANPLAYER_H_
