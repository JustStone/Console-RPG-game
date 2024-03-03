#include <iostream>
#include <curses.h>
#include <string>
#include <cstdlib>

#include "GameSystem.h"
#include "MazeGen.cpp"

using namespace std;

int main() {

  initscr();
  raw(); /* Line buffering disabled */
  noecho(); /* Don't echo() while we do getch */
  curs_set(0);

  GameSystem gameSystem("/Users/ruslan/Desktop/fc3/level1");

  gameSystem.playGame();
}