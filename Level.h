#ifndef FC3_LEVEL_H
#define FC3_LEVEL_H
#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.h"

using namespace std;

class Level {
 public:
  Level();
  void load(string fileName, Player &player);
  void print();
  void restartGame();
  void movePlayer(char input, Player &player);
  void updateEnemies(Player &player);

  char getTile(int x, int y);

  void setTile(int x, int y, char tile);

 private:
  void processPlayerMove(Player &player, int targetX, int targetY);
  void processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY);
  string updateStats(string lvl, string health, string attack, string defense, string experience);
  void processNextLevel();
  void processPrevLevel();
  void processBonusLevel();

  void battleEnemy(Player &player, int targetX, int targetY);

  string _stats = "\n";
  string _message; // сообщение пользователю
  string _currentLevelName = "/Users/ruslan/Desktop/fc3/level1";
  int _currentLevelDigit = 1;
  vector<string> _levelData; //хранит СТРОКИ уровня
  bool _bonusLevel = false;
  pair<int, int> _bonusCoord;
  bool _bonusChecker = false;

  vector<Enemy> _enemies;
};

#endif //FC3_LEVEL_H
