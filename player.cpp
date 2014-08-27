#include "player.h"

Player::Player() {
  name = NULL;
}

Player::Player(char *new_name, int health) : Creature(health) {
  if (new_name) {
    name = new char[strlen(new_name) + 1];
    strcpy(name, new_name);
  }
}

Player::~Player() {
  if (name)
    delete[] name;
  name = NULL;
}

Player::Player(const Player &other) : Creature(other) {
  if (other.name) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
  }
  carry_capacity = other.carry_capacity;
  //damage_multiplier = other.damage_multiplier;
}

bool Player::operator==(Player &other) {
  return (strcmp(other.name, name) == 0) ? true : false; 
}

void Player::display() {
  cout << "Player name: " << name << endl;
  cout << "Health: " << health << endl;
}

/* Wizard */
/* Will not drop potions */

Wizard::Wizard() {
  carry_capacity = 3;
}

Wizard::Wizard(char *name, int health) : Player(name, health) {
  carry_capacity = 3;
}

Wizard::~Wizard() {
}

Wizard::Wizard(const Wizard &other) : Player(other) {
}

void Wizard::loot(Inventory &other_inv) {
  if (get_n_items() >= carry_capacity) {
    return; 
  }
  copy_inventory(other_inv);
}

void Wizard::drop(Item &to_drop) {
  Item compare("potion", 0);
  if (compare == to_drop) {
    return;
  }
  remove_item(to_drop);
}

/* Knight */
/* no restrictions */

Knight::Knight() {
  carry_capacity = 20;
}

Knight::Knight(char *name, int health) : Player(name, health) {
  carry_capacity = 20;
}

Knight::~Knight() {
}

Knight::Knight(const Knight &other) : Player(other) {
}

void Knight::loot(Inventory &other_inv) {
  copy_inventory(other_inv);
}

void Knight::drop(Item &to_drop) {
  remove_item(to_drop);
}

/* Archer */
/* Only picks up gold */

Archer::Archer() {
  carry_capacity = 5;
}

Archer::Archer(char *name, int health) : Player(name, health) {
  carry_capacity = 5;
}

Archer::~Archer() {
}

Archer::Archer(const Archer &other) : Player(other) {
}

void Archer::loot(Inventory &other_inv) {
  if (get_n_items() >= carry_capacity) {
    return; 
  }
  Item i("gold", 100);
  copy_inventory(other_inv, i);
}

void Archer::drop(Item &to_drop) {
  remove_item(to_drop);
}

/* class of stuff for managing players */

/*
 *player_nocde::player_node() {
 *}
 */

player_node::player_node(int size) {
  player_list = new Player*[size];
  active_player = 0;
  n_items = 0;
  capacity = size;
  next = NULL;
}

player_node::~player_node() {
  remove_all();
}

int player_node::add_player(Player &p) {
  if (n_items < capacity) {
    //player_list[n_items] = &p;
    //downcast p
    const Wizard *w = dynamic_cast<const Wizard *>(&p);
    const Knight *k = dynamic_cast<const Knight *>(&p);
    const Archer *a = dynamic_cast<const Archer *>(&p);
    if (w)
      player_list[n_items] = new Wizard(*w);
    if (k)
      player_list[n_items] = new Knight(*k);
    if (a)
      player_list[n_items] = new Archer(*a);
    else if (!w && !k && !a)
      return 0;
    n_items++;
    return 1;
  }
  return 0;
}

player_node *&player_node::next_item() {
  return next;
}

void player_node::connectNext(player_node *other) {
  next = other;
}

void player_node::remove_all() {
  for (int i = 0; i < n_items; i++)
    delete player_list[i];
  n_items = 0;
}

void player_node::display_all() {
  for (int i = 0; i < n_items; i++) {
    player_list[i]->display();
  }
}

/* return the currently playing player in the node */
Player *player_node::get_active_player() {
  if (active_player < n_items) {
    ++active_player; 
    return player_list[active_player-1];
  } else {
    active_player = 0;
    return NULL;
  }
}

/* Player collection */

player_collection::player_collection() {
  head = NULL;
  active_player = NULL;
}

player_collection::~player_collection() {
  remove_all();
  head = NULL;
}

void player_collection::add_player(Player &to_add) {
  head = add_player(to_add, head);
}

player_node* player_collection::add_player(Player &to_add, player_node *context) {
  if (!context) {
    context = new player_node;
    context->add_player(to_add);

    /* make it circular, so it's easier to loop through */
    context->connectNext(head);

    return context;
  }
  if (!context->add_player(to_add)) //if full
    context->connectNext(add_player(to_add, context->next_item()));
  return head;
}

void player_collection::remove_all() {
  player_node *current = head;
  player_node *next;
  while (current) {
    next = current->next_item();
    delete current;
    current = next;
  }
  head = NULL;
}

void player_collection::display_all() {
  player_node *c = head;
  do {
    c->display_all();
    c = c->next_item();
  } while (c != head && c);
}

Player *player_collection::get_active_player() {
  if (!active_player)
    active_player = head;

  Player *to_return = active_player->get_active_player();
  while (!to_return) {
    /* what if there is no next array? */
    /* TODO wont need to do this if a single element in the LL points to itself, but for now, eh */
    player_node *n = active_player->next_item();
    if (n)
      active_player = n;
    /* then just call get_active_player() again on the current arr */
    to_return = active_player->get_active_player();
  }
  return to_return;
}
