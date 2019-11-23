#ifndef THEGAME__RANDOMPLAYER_H_
#define THEGAME__RANDOMPLAYER_H_

#include "iPlayer.h"
#pragma once
class randomPlayer : public iPlayer {
  void play(iPlayer& enemy, std::string player) override;
  void shipSet() override;
};

#endif //THEGAME__RANDOMPLAYER_H_
