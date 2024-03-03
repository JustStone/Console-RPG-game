#include "GameSystem.h"
#include <curses.h>

#include <iostream>

//Конструктор, начинающий игру
GameSystem::GameSystem(string levelFileName) {

  _player.init(1, 100, 10, 10, 0);

  _level.load(levelFileName, _player);
}

void GameSystem::playGame() {
  while (true) {
    _level.print();
    playerMove();
    _level.updateEnemies(_player);
  }
}

void GameSystem::playerMove() {
  char input;
  printw("Enter a move command (w/s/a/d): ");

  input = getch();//ждем действие игрока
  clear();//чистим прошлое состояние после действия

  _level.movePlayer(input, _player);
}
