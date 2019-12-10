cmake_minimum_required(VERSION 3.15)
project(theGame)

set(CMAKE_CXX_STANDARD 17)

add_executable(theGame main.cpp iPlayer.h randomPlayer.h iBoard.h curPlayerBoard.h iShip.h humanPlayer.h enemyBoard.h game.h)
