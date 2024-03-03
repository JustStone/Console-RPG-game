//
// Created by Руслан Пряженцев on 14.04.2023.
//

#ifndef FC3_PLAYER_H
#define FC3_PLAYER_H

class Player {
 public:
  Player();
  void init(int lvl, int health, int attack, int defense, int experience);

  void setPosition(int x, int y);
  void setHealth(int health);
  void setDefense(int defense);
  void setAttack(int attack);

  void getPosition(int &x, int &y) const;
  int getHealth() const;
  int getExperience() const;
  int getDefense() const;
  int getLvl() const;
  int getAttack() const;

  void addExperience(int experience);
  int attack() const;

//    int takeDamage(int attack);



 private:
  int _lvl;
  int _health;
  int _attack;
  int _defense;
  int _experience;
  int _x;
  int _y;

};

#endif //FC3_PLAYER_H
