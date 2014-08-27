#ifndef DUNGEON_H
#define DUNGEON_H

#include "room.h"

#define MAXROOMS 10

class Dungeon {
  public:
    Dungeon();
    ~Dungeon();
    Dungeon(const Dungeon &);
    int add_room(const Room &);
    void link(Room &, Room &, char *, bool=false);
    void display_all();
    void display_adjacent(Room &);
    void start(Player &);
    void fight(Player &, Room *);
  private:
    Room *rooms; //adjacency list
    int num_rooms;
    void display_all(Room &);
    void display_adjacent(Hall *);
    void add_edge(Hall *&, Room &, char *);
    void start(Room *);
    Room *get_next(Room &, char *);

    int find_location(Room &);
};

#endif
