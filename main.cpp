#include <getopt.h>
#include <iostream>
#include <string>
#include "humanPlayer.h"
#include "game.h"
#include "randomPlayer.h"

void helpMessage(){
  std::cout << "help" << std::endl;
}

auto getPlayer(const std::string& playerType) -> iPlayer*{
  if (playerType == "random")
    return new randomPlayer();
  if (playerType == "human")
    return new humanPlayer();
  //if (playerType == "smart")
    //return new randomPlayer;
  return new randomPlayer();
}

auto main(int argc, char**argv) -> int{
  const struct option long_options[] = {{"help", 0, nullptr, 'h'},
                                        {"count", 1, nullptr, 'c'},
                                        {"first", 1, nullptr, 'f'},
                                        {"second", 1, nullptr, 's'}};
  int rez = 0;
  int i = 0;
  int count = 1;
  std::string first = "random";
  std::string second = "random";
  while ((rez = getopt_long(argc, argv, "c:f:s:h", long_options, nullptr)) != -1) {
    switch (rez) {
      case 'c': {
        count = atoi(optarg);
        i += 2;
        break;
      }
      case 'f': {
        first = optarg;
        i += 2;
        break;
      }
      case 's': {
        second = optarg;
        i += 2;
        break;
      }
      case 'h': {
        helpMessage();
        exit(0);
      }
      case '?': {
        printf("Wrong argument\nWrite --help for info\n");
        exit(0);
      }
      default:;
    }
  }

  if (((first != "human") && (first != "random")) || ((second != "human") && (second != "random"))){
    std::cout << "Wrong player type.\n";
    return -1;
  }

  int score[2] = {0};
  for (auto k = 0; k < count; ++k) {
    auto a = getPlayer(first);
    auto b = getPlayer(second);
    if (count > 1) {
      std::cout << "SCORE: \n" << "First player: " << score[0];
      std::cout << "   Second player: " << score[1] << std::endl;
      std::cout << k + 1 << " game begins.\n";
      std::cout << "Press enter to continue.\n";
      getchar();
    }
    score[game::start(*a, *b)]++;
    delete a;
    delete b;
  }
  std::cout << "SCORE: \n" << "First player: " << score[0];
  std::cout << "   Second player: " << score[1] << std::endl;

  if (score[0] == score[1])
    std::cout << "Draw!\n";
  else
    std::cout << ((score[1] > score[0]) ? "Second" : "First") << " player won the game!\n";


  return 0;
}
