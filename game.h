#ifndef THEGAME__GAME_H_
#define THEGAME__GAME_H_

#include "iPlayer.h"
class game {
 public:
  static auto start(iPlayer &first, iPlayer &second) -> int;
};


auto game::start(iPlayer &first, iPlayer &second) -> int {
  std::cout << "First player\n";
  first.shipSet();
  clearScreen();
  std::cout << "Second player\n";
  second.shipSet();
  clearScreen();

  while ((first.shipAmount != 0) && (second.shipAmount != 0)) {
    first.play(second, "First");
    second.play(first, "Second");
  }
  std::cout << "GG\n";
  std::cout << "Press enter to continue\n";
  getchar();
  return (first.shipAmount == 0) ? 1 : 0;
}

#endif //THEGAME__GAME_H_
