#include "Enemy.h"
#include <random>
#include <ctime>

Enemy::Enemy(string name, char tile, int level, int attack, int defense, int health, int xp) {
  _name = name;
  _tile = tile;
  _attack = attack;
  _defense = defense;
  _health = health;
  _experienceValue = xp;
}

void Enemy::setPosition(int x, int y) {
  _x = x;
  _y = y;
}

void Enemy::setHealth(int health) {
  _health = health;
}

void Enemy::setDefense(int defense) {
  if (_defense <= 0)
    _defense = 0;
  _defense = defense;
}

void Enemy::getPosition(int &x, int &y) const {
  x = _x;
  y = _y;
}

string Enemy::getName() {
  return _name;
}

int Enemy::getDefense() const {
  if (_defense <= 0)
    return 0;
  return _defense;
}

char Enemy::getMove(int playerX, int playerY) const {
  static default_random_engine randEngine(time(nullptr));
  uniform_int_distribution<int> moveRoll(0, 6);

  int distance;
  int dx = _x - playerX;
  int dy = _y - playerY;
  int adx = abs(dx);
  int ady = abs(dy);

  distance = adx + ady;

  if (distance <= 5) {
    //Moving along X axis
    if (adx > ady) {
      if (dx > 0) {
        return 'a';
      } else {
        return 'd';
      }
    } else { //Move along Y axis
      if (dy > 0) {
        return 'w';
      } else {
        return 's';
      }
    }
  }

  int randomMove = moveRoll(randEngine);
  switch (randomMove) {
    case 0:return 'a';
    case 1:return 'w';
    case 2:return 's';
    case 3:return 'd';
    default:return '.';// don't move
  }
}

char Enemy::getTile() const {
  return _tile;
}

int Enemy::getHealth() const {
  if (_health <= 0)
    return 0;
  return _health;
}

int Enemy::getExperience() const {
  return _experienceValue;
}

int Enemy::attack() const {
  static default_random_engine randomEngine(time(NULL) * 2);
  uniform_int_distribution<int> attackRoll(0, _attack);

  return attackRoll(randomEngine);
}

//int Enemy::takeDamage(int attack) {
//    attack -= _defense;
//    if (attack > 0){
//
//        _health -= attack;
//
//        if (_health <= 0)
//            return _experienceValue;
//    }
//    return 0;
//}





