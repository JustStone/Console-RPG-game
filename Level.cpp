#include <fstream>
#include <iostream>
#include <cstdio>
#include <curses.h>

#include "Level.h"
#include "GameSystem.h"
#include "MazeGen.cpp"

Level::Level() = default;

void Level::load(string fileName, Player &player) {
  //считываем данные с файла (строки уровня) - загружаем уровень
  _levelData.clear();
  _enemies.clear();
  ifstream file;
  string a = "⇝";

  file.open(fileName.c_str());
  if (file.fail()) {
    perror(fileName.c_str());//https://otvet.mail.ru/question/179219545
    exit(1);
  }

  string line;

  while (getline(file, line)) {
    _levelData.push_back(line);
  }

  file.close();

  //Игровой процесс
  char tile;
  //Тупо проходимся по всем символам поля игры
  for (int i = 0; i < _levelData.size(); i++) {
    for (int j = 0; j < _levelData[i].size(); j++) {
      tile = _levelData[i][j];
      switch (tile) {
        case '@':player.setPosition(j, i);
          break;
        case '*':_enemies.emplace_back("Star", tile, 1, 30, 15, 50, 51); //hour
          _enemies.back().setPosition(j, i);
          break;
        case '^':_enemies.emplace_back("Bird", tile, 7, 150, 100, 400, 101); //hour
          _enemies.back().setPosition(j, i);
          break;
        case '$':_enemies.emplace_back("Snake", tile, 10, 300, 200, 700, 201); //hour
          _enemies.back().setPosition(j, i);
          break;
        case 'B':_enemies.emplace_back("Boss", tile, 16, 550, 400, 3700, 10000); //hour
          _enemies.back().setPosition(j, i);
          break;
      }
    }
  }
}

void Level::print() {
  printw(_stats.c_str());
  printw(_message.c_str());
  for (const auto &i : _levelData)
    printw("%s\n", i.c_str());
  printw("\n");
}

void Level::restartGame() {
  clear();
  GameSystem gameSystem("/Users/ruslan/Desktop/fc3/level1");
  gameSystem.playGame();
}

string Level::updateStats(string lvl, string health, string attack, string defense, string experience){
  string result = "Level: " + lvl + "\n"
      + "Health: " + health + "\n"
      + "Attack: " + attack + "\n"
      + "Defense: " + defense + "\n"
      + "Experience: " + experience + "\n\n\n";
    return result;
}


void Level::movePlayer(char input, Player &player) {
  int playerX;
  int playerY;
  player.getPosition(playerX, playerY);
  _message = "\n";
  _stats = updateStats(to_string(player.getLvl()), to_string(player.getHealth()),
                       to_string(player.getAttack()), to_string(player.getDefense()),
                       to_string(player.getExperience()));
//  _stats += "Level: " + to_string(player.getLvl()) + "\n"
//      + "Health: " + to_string(player.getHealth()) + "\n"
//      + "Attack: " + to_string(player.getAttack()) + "\n"
//      + "Defense: " + to_string(player.getDefense()) + "\n"
//      + "Experience: " + to_string(player.getExperience()) + "\n\n\n";

  switch (input) {
    case 'w':
    case 'W':processPlayerMove(player, playerX, playerY - 1);
      break;
    case 's':
    case 'S':processPlayerMove(player, playerX, playerY + 1);
      break;
    case 'a':
    case 'A':processPlayerMove(player, playerX - 1, playerY);
      break;
    case 'd':
    case 'D':processPlayerMove(player, playerX + 1, playerY);
      break;
    case '0':restartGame();
    default:_message = "Invalid input! \n";
      break;
  }
}

void Level::updateEnemies(Player &player) {
  char aiMove;
  int playerX;
  int playerY;
  int enemyX;
  int enemyY;

  player.getPosition(playerX, playerY);

  for (int i = 0; i < _enemies.size(); i++) {
    aiMove = _enemies[i].getMove(playerX, playerY);
    _enemies[i].getPosition(enemyX, enemyY);
    switch (aiMove) {
      case 'w':processEnemyMove(player, i, enemyX, enemyY - 1);
        break;
      case 's':processEnemyMove(player, i, enemyX, enemyY + 1);
        break;
      case 'a':processEnemyMove(player, i, enemyX - 1, enemyY);
        break;
      case 'd':processEnemyMove(player, i, enemyX + 1, enemyY);
        break;
    }
  }

}

char Level::getTile(int x, int y) {
  return _levelData[y][x]; // y - rows, x - cols
}

void Level::setTile(int x, int y, char tile) {
  _levelData[y][x] = tile;
}

void Level::processNextLevel() {
  //сохраняем прошлый уровень -------
  ofstream file;
  string fName = _currentLevelName;
  if (_currentLevelName[_currentLevelName.size() - 1] != 'e')
    fName += "save";
  file.open(fName);
  if (file.fail()) {
    perror(fName.c_str());//https://otvet.mail.ru/question/179219545
    exit(1);
  }
  string line;
  for (const auto &i : _levelData) {
    file << i + "\n";
  }
  file.close();
  //----------------------------------
  _currentLevelDigit++;
  if (_currentLevelName[_currentLevelName.size() - 1] != 'e')
    _currentLevelName = _currentLevelName.erase(_currentLevelName.size() - 1, 1) + to_string(_currentLevelDigit);
  else if (_bonusChecker == 0)
    _currentLevelName = _currentLevelName.erase(_currentLevelName.size() - 5, 5) + to_string(_currentLevelDigit) + "save";
  else{
    _currentLevelName = _currentLevelName.erase(_currentLevelName.size() - 5, 5) + to_string(_currentLevelDigit);
    _bonusChecker = 0;
  }

}

void Level::processPrevLevel() {
  //сохраняем прошлый уровень -------
  ofstream file;
  string fName = _currentLevelName;
  if (_currentLevelName[_currentLevelName.size() - 1] != 'e')
    fName += "save";
  file.open(fName);
  if (file.fail()) {
    perror(fName.c_str());//https://otvet.mail.ru/question/179219545
    exit(1);
  }
  string line;
  for (const auto &i : _levelData) {
    file << i + "\n";
  }
  file.close();
  //----------------------------------
  _currentLevelDigit--;
  if (_currentLevelName[_currentLevelName.size() - 1] != 'e')
    _currentLevelName =
        _currentLevelName.erase(_currentLevelName.size() - 1, 1) + to_string(_currentLevelDigit) + "save";
  else
    _currentLevelName =
        _currentLevelName.erase(_currentLevelName.size() - 5, 5) + to_string(_currentLevelDigit) + "save";
}

void Level::processBonusLevel() {
  //сохраняем уровень c которого пришли -------
  ofstream file;
  string fName = _currentLevelName;
  if (_currentLevelName[_currentLevelName.size() - 1] != 'e')
    fName += "save";
  file.open(fName);
  if (file.fail()) {
    perror(fName.c_str());//https://otvet.mail.ru/question/179219545
    exit(1);
  }
  string line;
  for (const auto &i : _levelData)
    file << i + "\n";
  file.close();
  if (_currentLevelName[_currentLevelName.size() - 1] != 'e'){
    _bonusChecker = true;
    _currentLevelName = _currentLevelName.erase(_currentLevelName.size() - 1, 1) + to_string(_currentLevelDigit) + "save";
  }
  //Генерируем лабиринт----------------
  ofstream file2;
  string fName2 = "/Users/ruslan/Desktop/fc3/bonuslevel";
  file2.open(fName2);
  if (file2.fail()) {
    perror(fName.c_str());//https://otvet.mail.ru/question/179219545
    exit(1);
  }
  vector<vector<int> > arr;
  Labyrinth lab;

  int x = 15;
  int y = 15  ;
  arr = lab.create_labyrinth(x, y);

  for (int i = 0; i < y; ++i) {
    for (int j = 0; j < x; ++j) {
      if (arr[i][j] == 1)
        file2 << '#';
      if (arr[i][j] == 0 || arr[i][j] == 4)
        file2 << '.';
      if (arr[i][j] == 5)
        file2 << '?';
    }
    file2 << '\n';
  }
  file2.close();
  _bonusLevel = true;

  //----------------------------------
}

void Level::processPlayerMove(Player &player, int targetX, int targetY) {
  int playerX;
  int playerY;
  player.getPosition(playerX, playerY);

  char moveTile = getTile(targetX, targetY);
  switch (moveTile) {
    case '.':player.setPosition(targetX, targetY);
      setTile(playerX, playerY, '.');
      setTile(targetX, targetY, '@');
      break;
//    case '#':_message = "You ran into a wall!\n";
//      break;
    case '>':setTile(playerX, playerY, '.');
      processNextLevel();
      load(_currentLevelName, player);
      player.setPosition(3, 2);
      setTile(3, 2, '@');
      break;
    case '<':setTile(playerX, playerY, '.');
      processPrevLevel();
      load(_currentLevelName, player);
      player.setPosition(60, 19);
      setTile(60, 19, '@');
      break;
    case '?':setTile(playerX, playerY, '.');
      if (!_bonusLevel) {
        _bonusCoord = make_pair(targetX, targetY);
        setTile(targetX, targetY, '.');
        processBonusLevel();
        load("/Users/ruslan/Desktop/fc3/bonuslevel", player);
        player.setPosition(1, 1);
        setTile(1, 1, '@');
      } else {
        load(_currentLevelName, player);
        player.setPosition(_bonusCoord.first, _bonusCoord.second);
        setTile(_bonusCoord.first, _bonusCoord.second, '@');
        _bonusLevel = false;
      }
      break;
    case '+':player.setPosition(targetX, targetY);
      setTile(playerX, playerY, '.');
      setTile(playerX, playerY, '.');
      setTile(targetX, targetY, '@');
      player.setHealth(player.getHealth() + 70);
      _stats = "";
      _stats = updateStats(to_string(player.getLvl()), to_string(player.getHealth()),
                           to_string(player.getAttack()), to_string(player.getDefense()),
                           to_string(player.getExperience()));
      break;
    case '!':player.setPosition(targetX, targetY);
      setTile(playerX, playerY, '.');
      setTile(targetX, targetY, '@');
      player.setAttack(player.getAttack() + 30);
      _stats = "";
      _stats = updateStats(to_string(player.getLvl()), to_string(player.getHealth()),
                           to_string(player.getAttack()), to_string(player.getDefense()),
                           to_string(player.getExperience()));
      break;
    case '=':player.setPosition(targetX, targetY);
      setTile(playerX, playerY, '.');
      setTile(targetX, targetY, '@');
      player.setDefense(player.getDefense() + 25);
      _stats = "";
      _stats = updateStats(to_string(player.getLvl()), to_string(player.getHealth()),
                           to_string(player.getAttack()), to_string(player.getDefense()),
                           to_string(player.getExperience()));
      break;
    case '%':player.setPosition(targetX, targetY);
      setTile(playerX, playerY, '.');
      setTile(targetX, targetY, '@');
      player.addExperience(151);
      _stats = "";
      _stats = updateStats(to_string(player.getLvl()), to_string(player.getHealth()),
                           to_string(player.getAttack()), to_string(player.getDefense()),
                           to_string(player.getExperience()));
      break;

    default: //противник
//            battleEnemy(player, targetX, targetY);
      break;
  }

}

void Level::processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY) {
  int playerX;
  int playerY;
  int enemyX;
  int enemyY;

  _enemies[enemyIndex].getPosition(enemyX, enemyY);
  player.getPosition(playerX, playerY);

  char moveTile = getTile(targetX, targetY);
  switch (moveTile) {
    case '.':_enemies[enemyIndex].setPosition(targetX, targetY);
      setTile(enemyX, enemyY, '.');
      setTile(targetX, targetY, _enemies[enemyIndex].getTile());
      break;
    case '@':battleEnemy(player, enemyX, enemyY);
      break;
    default:
      break;
  }
}

void Level::battleEnemy(Player &player, int targetX, int targetY) {
  int enemyX;
  int enemyY;
  int PlayerX;
  int PlayerY;
  int attackRoll;
  string enemyName;
  player.getPosition(PlayerX, PlayerY);//чтобы вычислить место смерти

  for (int i = 0; i < _enemies.size(); i++) {
    _enemies[i].getPosition(enemyX, enemyY);
    enemyName = _enemies[i].getName();
    _message = "";

    if (targetX == enemyX && targetY == enemyY) {

      //player attack
      attackRoll = player.attack();
      if ((_enemies[i].getDefense() - attackRoll) >= 0)
        _enemies[i].setDefense(_enemies[i].getDefense() - attackRoll);
      else {
        _enemies[i].setDefense(_enemies[i].getDefense() - attackRoll);
        _enemies[i].setHealth(_enemies[i].getHealth() + _enemies[i].getDefense() - attackRoll);
      }

      if (attackRoll == 0)
        _message += "Player missed! \n";
      else
        _message += "You dealt " + to_string(attackRoll) + " damage" + " to " + enemyName +
            +"(Health of enemy: " + to_string(_enemies[i].getHealth()) + " [" + to_string(_enemies[i].getDefense()) + "]" ")" + "\n";

      if (_enemies[i].getHealth() <= 0) {
        setTile(targetX, targetY, '.');
        _message.pop_back();
        _message += " " + enemyName + " died! \n";
        if(enemyName != "Boss")
          _message += " " + enemyName + " died! \n";
        else
          restartGame();
        player.addExperience(_enemies[i].getExperience());

        //удаляем труп из массива врагов
        _enemies[i] = _enemies.back();
        _enemies.pop_back();
        i--;

        return;
      }

      //monster attack
      attackRoll = _enemies[i].attack();
      if ((player.getDefense() - attackRoll) >= 0)
        player.setDefense(player.getDefense() - attackRoll);
      else {
        player.setDefense(player.getDefense() - attackRoll);
        player.setHealth(player.getHealth() + player.getDefense() - attackRoll);
      }

      _stats = "";
      _stats = updateStats(to_string(player.getLvl()), to_string(player.getHealth()),
                           to_string(player.getAttack()), to_string(player.getDefense()),
                           to_string(player.getExperience()));

      //DEAD
      if (player.getHealth() <= 0) {
        _message = "You are dead! Press any key 3 times for restart the game\n";
        player.setHealth(0);
        setTile(PlayerX, PlayerY, 'x');
        print();
        getch();
        getch();
        getch();
        restartGame();
      }
      return;
    }
  }
}




