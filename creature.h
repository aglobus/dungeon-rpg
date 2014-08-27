#ifndef CREATURE_H
#define CREATURE_H

#include "inventory.h"

class Creature : public Inventory {
  public:
    Creature();
    Creature(int health);
    ~Creature();
    Creature(const Creature &);
    Creature &operator=(const Creature &other);
  protected:
    int health;
};

#endif
