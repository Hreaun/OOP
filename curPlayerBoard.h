#ifndef THEGAME__CURPLAYERBOARD_H_
#define THEGAME__CURPLAYERBOARD_H_

#include "iBoard.h"
#pragma once

class curPlayerBoard : public iBoard {
  friend class humanPlayer;
 protected:
  iShip *table[10][10]{};
 public:
  std::vector<std::string> getBoard() override;
  curPlayerBoard(){
    for (auto &row : this->table) {
      for (auto &col : row)
        col = nullptr;
    }
  }
};

char symbolCase(iShip *curPoint, int x, int y){
  if (curPoint == nullptr) return '*';
  if (curPoint->isSunken()){
    return 'X';
  }
  if (curPoint->partDamaged(x, y)){
    return 'H';
  }
  return 'S';
}


std::vector<std::string> curPlayerBoard::getBoard() {
  std::vector<std::string> board(12);
  board[0] = "\t    YOUR BOARD\n";
  board[1] = "   ";
  for (char i = 0; i < 10; ++i) {
    board[1] += ((char)('A' + i));
    board[1] += "  ";
  }
  board[1]+= "\n";

  char c = 0;
  for (auto row = 0; row < 10; ++row) {
    board[row + 2] += std::to_string(row) + "  ";
    for (auto col = 0; col < 10; ++col) {
      c = symbolCase(this->table[row][col], col, row);
      board[row + 2] += (char)c;
      board[row + 2] += "  ";
    }
    board[row + 2] += "\n";
  }

  return board;
}


#endif //THEGAME__CURPLAYERBOARD_H_
