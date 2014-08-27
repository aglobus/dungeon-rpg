#ifndef PLAYER_H
#define PLAYER_H

#include "creature.h"

/* abstract base class */

class Player: public Creature {
  public:
    Player();
    Player(char *, int);
    virtual ~Player();
    Player(const Player &);
    /* Each type of player will have a weird set of loot and drop rules */
    virtual void loot(Inventory &) = 0;
    virtual void drop(Item &) = 0;
    //virtual void display() = 0;
    bool operator==(Player &);
    void display();
  protected:
    char *name;
    int carry_capacity; //maximum items can carry
    //int damage_multiplier; //keep this? TODO
};

/* derived classes from abstract base player */
/* the differences between the classes are sort of weak, but it's mostly to showcase that the ability to differentiate is there */

class Wizard : public Player {
  public:
    Wizard();
    Wizard(char *, int);
    ~Wizard();
    Wizard(const Wizard &);
    virtual void loot(Inventory &);
    virtual void drop(Item &);
};

class Knight : public Player {
  public:
    Knight();
    Knight(char *, int);
    ~Knight();
    Knight(const Knight &);
    virtual void loot(Inventory &);
    virtual void drop(Item &);
};

class Archer : public Player {
  public:
    Archer();
    Archer(char *, int);
    ~Archer();
    Archer(const Archer &);
    virtual void loot(Inventory &);
    virtual void drop(Item &);
};

/* class to manage multiple players */
/* LLL of arrays */

class player_node {
  public:
    //player_node();
    player_node(int size = 5);
    ~player_node();
    int add_player(Player &);
    player_node *& next_item();
    void connectNext(player_node *);
    void remove_all();
    void display_all();
    Player *get_active_player();
  private:
    /* data */
    Player **player_list; //array of base pointers
    player_node *next;
    int active_player; //index of active player
    int n_items;
    int capacity;
};

class player_collection {
  public:
    player_collection();
    ~player_collection();
    void add_player(Player &);
    void remove_all();
    void display_all();
    Player *get_active_player();
  private:
    /* data */
    player_node *head;
    player_node *active_player; //ptr to array that has the current player
    /* methods */
    player_node* add_player(Player &, player_node *);
};


#endif
