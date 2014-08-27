#include "manager.h"

/*
 * I don't have time to load/save the data from the disk, so here's just a little test function that adds some monsters/items/rooms and lets the player run through some basic rooms.
 * There's no real point/objective to this game other than to showcase the design and its OOP-ness. Hope it suffices.
 */

int main(int argc, const char *argv[])
{
  Manager m;
  m.create_sample_dungeon();
  m.start();
  return 0;
}
