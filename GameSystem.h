#ifndef FC3_GAMESYSTEM_H
#define FC3_GAMESYSTEM_H

#include "curses.h"
#include <string>

#include "Player.h"
#include "Level.h"

using namespace std;

class GameSystem {
 public:
  GameSystem(string levelFileName);

  void playGame();
  void playerMove();

 private:
  Level _level;
  Player _player;
};

#endif //FC3_GAMESYSTEM_H
