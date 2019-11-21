#include <getopt.h>
#include <iostream>
#include <string>
#include "humanPlayer.h"
#include "game.h"

void helpMessage(){
  std::cout << "help" << std::endl;
}

int main(int argc, char**argv){
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

  humanPlayer a;
  humanPlayer b;
  game::start(a, b);

  return 0;
}