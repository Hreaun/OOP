/*#include "randomPlayer.h"
#include <random>
void randomPlayer::play(iPlayer& enemy) {
  std::random_device r;
  std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
  std::mt19937 eng{seed};
  std::uniform_int_distribution<> dist(0,9);

  if(enemy.curPlBoard.table[dist(eng)][dist(eng)] == 'S'){

  }
}



void randomPlayer::shipSet() {
  std::random_device r;
  std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
  std::mt19937 eng{seed};
  std::uniform_int_distribution<> dist(0,9);
  int singleDecker = 4;
  int twoDecker = 3;
  int threeDecker = 2;
  int fourDecker = 1;

  while(singleDecker != 0) {
    int row = dist(eng);
    int col = dist(eng);
    if (this->curPlBoard.table[row][col] != 'S') {
     this->curPlBoard.table[row][col] = 'S';
      singleDecker--;
    }
  }

}*/
