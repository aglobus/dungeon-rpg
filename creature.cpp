#include "creature.h"

Creature::Creature() {
  health = 100;
}

Creature::Creature(int health) {
  /* Inventory's default constructor is invoked */
  this->health = health;
}

Creature::~Creature() {
  health = 0;
}

/* copy Creature's inventory over and the other health */
Creature::Creature(const Creature &other) : Inventory(other), health(other.health) {
}

Creature &Creature::operator=(const Creature &other) {
  Inventory::operator=(other); //set the other inventory equal to ours
  health = other.health;
  return *this;
}
