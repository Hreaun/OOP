#ifndef THEGAME__ENEMYBOARD_H_
#define THEGAME__ENEMYBOARD_H_

#include "iBoard.h"
#pragma once
class enemyBoard : public iBoard {
 public:
  char table[10][10] = {};
  std::vector<std::string> getBoard() override;
  enemyBoard(){
    for (auto &row : this->table) {
      for (auto &col : row)
        col = '+';
    }
  }
};

std::vector<std::string> enemyBoard::getBoard() {
  std::vector<std::string> board(12);
  board[0] = "\t\t\t\tENEMY'S BOARD\t\t\t\t\t\t\t\t";
  board[1] = "\t";
  for (char i = 0; i < 10; ++i) {
    board[1] += ((char) ('A' + i));
    board[1] += "\t";
  }
  board[1]+= "\t\t";

  for (auto row = 0; row < 10; ++row) {
    board[row + 2] += std::to_string(row) + "\t";
    for (auto col = 0; col < 10; ++col) {
      board[row + 2] += (char)table[row][col];
      board[row + 2] += "\t";
    }
    board[row + 2] += "\t\t";
  }

  return board;
}

#endif //THEGAME__ENEMYBOARD_H_
