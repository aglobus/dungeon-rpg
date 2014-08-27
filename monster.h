#ifndef MONSTER_H
#define MONSTER_H

#include "creature.h"

class Monster : public Creature {
  public:
    Monster();
    Monster(char *, float, int health = 100);
    ~Monster();
    Monster(const Monster &);
    Monster &operator=(const Monster &);
    /* returns 0 if defeated, 1 if still alive */ 
    int attack();
    void display();
  private:
    char *question;
    float correct_answer;
    bool is_alive;

    void create_monster(char *, float);
};

#endif
