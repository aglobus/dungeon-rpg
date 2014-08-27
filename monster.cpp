#include "monster.h"

Monster::Monster() {
  question = NULL;
  correct_answer = 0;
  is_alive = true;
}

/* alt constructor */
Monster::Monster(char *q, float ca, int health) : Creature(health) {
  create_monster(q, ca);
}

/* destructor */
Monster::~Monster() {
  delete[] question;
  question = NULL;
  correct_answer = 0;
  is_alive = false;
}

/* initialize from other monster */
Monster::Monster(const Monster &other) : is_alive(other.is_alive), Creature(other) {
  create_monster(other.question, other.correct_answer); 
}

Monster &Monster::operator=(const Monster &other) {
  /* copy over monster's stuff */
  delete[] question;
  question = NULL;
  create_monster(other.question, other.correct_answer);
  is_alive = other.is_alive;

  Creature::operator=(other);
  return *this; 
}

int Monster::attack() {
  cout << question << endl;
  float answer;
  cin >> answer;
  is_alive = (answer == correct_answer) ? 0 : 1;
  return is_alive;
}

void Monster::display() {
  cout << endl;
  cout << "The question: ";
  cout << question << endl;
  cout << "The inventory this monster has: " << endl;
  Inventory::display();
  //cout << "status: " << ((is_alive) ? "unanswered" : "answered") << endl;
}

void Monster::create_monster(char *q, float ca) {
  if (q) {
    question = new char[strlen(q) + 1];
    strcpy(question, q);
  } else {
    question = NULL;
  }
  correct_answer = ca;
  is_alive = true;
}
