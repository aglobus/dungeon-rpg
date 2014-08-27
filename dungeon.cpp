#include "dungeon.h"

Dungeon::Dungeon() {
  rooms = new Room[MAXROOMS];
  num_rooms = 0;
}

Dungeon::~Dungeon() {
  delete[] rooms;
  rooms = NULL;
  num_rooms = 0;
}

Dungeon::Dungeon(const Dungeon &other) {
}

int Dungeon::add_room(const Room &to_add) {
  if (num_rooms <= MAXROOMS) {
    rooms[num_rooms] = to_add;
    num_rooms++;
    return 1;
  }
  return 0;
}

void Dungeon::link(Room &one, Room &two, char *direction, bool secret) {
  int index = find_location(one);
  if (index < 0)
    return;
  rooms[index].link(two, direction, secret);
}

void Dungeon::display_all() {
  for (int i = 0; i < num_rooms; i++) {
    rooms[i].display();
  }
}

void Dungeon::display_adjacent(Room &to_display) {
  to_display.display_adjacent();
}

void Dungeon::start(Player &p) {
  cout << "The objective of the game is to get to the dormitory." << endl;
  if (rooms) {
    fight(p, rooms[0].fight(p));
  }

}

void Dungeon::fight(Player &p, Room *next_room) {
  int index = find_location(*next_room);
  Room *n = rooms[index].fight(p);
  if (!n) {
    cout << "Dungeon completed!" << endl;
    return;
  }
  fight(p, n);
}

int Dungeon::find_location(Room &to_find) {
  for (int i = 0; i < num_rooms; i++)
    if (rooms[i] == to_find)
      return i;
  return -1;
}
