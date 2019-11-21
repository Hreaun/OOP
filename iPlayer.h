#ifndef THEGAME__IPLAYER_H_
#define THEGAME__IPLAYER_H_
#include "curPlayerBoard.h"
#include "enemyBoard.h"
#pragma once

class iPlayer {
 public:
    iPlayer() = default;
    ~iPlayer() = default;
    curPlayerBoard curPlBoard;
    enemyBoard enmBoard;
    int shipAmount{};

    virtual void play(iPlayer& enemy, std::string player) = 0;
    virtual void shipSet() = 0;
    virtual void deadLabel(iPlayer &enemy, int x, int y) = 0;
};

#endif //THEGAME__IPLAYER_H_
