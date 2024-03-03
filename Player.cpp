//
// Created by Руслан Пряженцев on 14.04.2023.
//

#include "Player.h"
#include <random>
#include <ctime>

#include <curses.h>

using namespace std;

Player::Player() {
  _x = 0;
  _y = 0;
}

void Player::init(int lvl, int health, int attack, int defense, int experience) {
  _lvl = lvl;
  _health = health;
  _attack = attack;
  _defense = defense;
  _experience = experience;
}

void Player::setPosition(int x, int y) {
  _x = x;
  _y = y;
}

void Player::setHealth(int health) {
  _health = health;
}

void Player::setDefense(int defense) {
  if (_defense <= 0)
    _defense = 0;
  _defense = defense;
}

void Player::setAttack(int attack){
  _attack = attack;
}



void Player::getPosition(int &x, int &y) const {
  x = _x;
  y = _y;
}

int Player::getHealth() const {
  if (_health <= 0)
    return 0;
  return _health;
}

int Player::getExperience() const {
  return _experience;
}

int Player::getDefense() const {
  if (_defense <= 0)
    return 0;
  return _defense;
}

int Player::getLvl() const {
  return _lvl;
}

int Player::getAttack() const {
  return _attack;
}

int Player::attack() const {
  static default_random_engine randomEngine(time(NULL));
  uniform_int_distribution<int> attackRoll(0, _attack);

  return attackRoll(randomEngine);
}

void Player::addExperience(int experience) {
  _experience += experience;

  //levelup
  while (_experience > 150) {
    _experience -= 150;
    _attack += 20;
    _defense += 10;
    _health += 30;
    _lvl++;
  }
}


//int Player::takeDamage(int attack) {
//    attack -= _defense;
//    if (attack > 0){
//
//        _health -= attack;
//
//        if (_health <= 0)
//            return 1;
//    }
//    return 0;
//}







