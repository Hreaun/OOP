#ifndef THEGAME__ENEMYBOARD_H_
#define THEGAME__ENEMYBOARD_H_

#include "iBoard.h"
#pragma once
class enemyBoard : public iBoard {
 public:
  char table[10][10] = {};
  auto getBoard() -> std::vector<std::string> override;
  enemyBoard(){
    for (auto &row : this->table) {
      for (auto &col : row)
        col = '+';
    }
  }
};

auto enemyBoard::getBoard() -> std::vector<std::string> {
  std::vector<std::string> board(12);
  board[0] = "\t    ENEMY'S BOARD\t\t\t";
  board[1] = "   ";
  for (char i = 0; i < 10; ++i) {
    board[1] += ((char) ('A' + i));
    board[1] += "  ";
  }
  board[1]+= "\t\t";

  for (auto row = 0; row < 10; ++row) {
    board[row + 2] += std::to_string(row) + "  ";
    for (auto col = 0; col < 10; ++col) {
      board[row + 2] += (char)table[row][col];
      board[row + 2] += "  ";
    }
    board[row + 2] += "\t\t";
  }

  return board;
}

#endif //THEGAME__ENEMYBOARD_H_
