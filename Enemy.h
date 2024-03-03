#ifndef FC3_ENEMY_H
#define FC3_ENEMY_H

#include <string>

using namespace std;

class Enemy {

 public:
  Enemy(string name, char tile, int level, int attack, int defense, int health, int xp);

  void setPosition(int x, int y);
  void setHealth(int health);
  void setDefense(int defense);

  void getPosition(int &x, int &y) const;
  string getName();
  char getTile() const;
  char getMove(int playerX, int playerY) const;
  int getHealth() const;
  int getExperience() const;
  int getDefense() const;

  int attack() const;
  int takeDamage(int attack);

  //AI



 private:
  string _name;
  char _tile;

  int _attack;
  int _defense;
  int _health;
  int _experienceValue;

  int _x;
  int _y;
};

#endif //FC3_ENEMY_H
