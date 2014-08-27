#ifndef ROOM_H
#define ROOM_H

#include "inventory.h"
#include "monster.h"
#include "player.h"

#define MAXMONSTERS 5

class Room : public Inventory {
  public:
    Room();
    Room(char *);
    ~Room();
    Room(const Room &);
    Room &operator=(const Room &);
    bool operator==(const Room &);
    void display(); //display the room's contents
    void display_adjacent(); //show rooms that are adjacent to us
    int add_monster(Monster &); //add a monster to *monsters
    void link(Room &, char *, bool = false); //insert
    void unlink(Room &); //remove
    void unlink_all(); //remove-all rooms in our LLL
    Room* fight(Player &);
    bool is_solo(); //returns whether there are any adjacent rooms or not
  protected:
    Monster **monsters; //array of pointers to monsters
    int num_monsters; //# of monsters in the room
    char *description;
  private:
    class Hall *head; //a room class manages a LLL or adjacent rooms
    Hall *copy(Hall *);
    void copy_room(const Room &);
    void create_room(char *); //sets the room description to arg
    Hall *insert(Room &, Hall *, char *, bool = false);
    Hall *remove(Room &, Hall *);
    Hall *retrieve(char *, Hall *);
    void print(Hall *); //print LL
};

/* node */
class Hall : public Room {
  public:
    Hall();
    ~Hall();
    Hall(const Hall &);
    Hall(const Room &); //take in an argument about secrecy? TODO
    bool operator==(const Hall &);
    Hall *&get_next();
    char *get_direction();
    void set_direction(char *);
    void set_secret(bool);
    void connect_next(Hall *);
    bool compare_direction(char *);
    bool display();
  private:
    Hall *next;
    char *direction;
    bool secret;
};

#endif
