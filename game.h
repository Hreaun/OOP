#ifndef THEGAME__GAME_H_
#define THEGAME__GAME_H_

#include "iPlayer.h"
class game {
 public:
  static void start(iPlayer &first, iPlayer &second);
};


void game::start(iPlayer &first, iPlayer &second) {
  std::cout << "First player\n";
  first.shipSet();
  std::cout << "Second player\n";
  second.shipSet();

  while ((first.shipAmount != 0) && (second.shipAmount != 0)) {
    first.play(second, "first");
    second.play(first, "second");
  }
  std::cout << "GG\n";
}

#endif //THEGAME__GAME_H_
