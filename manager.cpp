#include "manager.h"

Manager::Manager() {
  dungeon = new Dungeon();
  players = new player_collection();
}

Manager::~Manager() { 
  delete players;
  delete dungeon;
  players = NULL;
  dungeon = NULL;
}

Manager::Manager(const Manager &other) {
}

void Manager::start() {
 /* add players */
  cout << "how many players would you like to add?" << endl;
  int i;
  cin >> i;
  cin.get();
  for (int j = 0; j < i; j++)
    add_player();

  players->display_all();

  Player *current;
  current = players->get_active_player();
  cout << endl << "Current player is: " << endl;
  current->display();
  cout << endl;
  while (true) {
    print_usage();
    switch(get_selection()) {
      case 's':
        start(current);
        break;
      case 'l':
        current->Inventory::display();
        break;
      case 'd':
        drop(*current); 
        break;
      case 'n':
        current = players->get_active_player();
        cout << endl << "Current player is: " << endl;
        current->display();
        break;
      case 'q':
        players->remove_all();
        return;
      default:
        print_usage();
    }
  }
}

void Manager::create_sample_dungeon() {
  /* create some sample monsters */
  Monster m1("What is 5+3?", 8);
  Monster m2("What is 3*5?", 15);
  Monster m3("What is 2-9?", -7);
  Monster m4("What is 5-6?", -1);
  Monster m5("What is 7*3?", 21);
  Monster m6("What is 8-4?", 4);

  /* create some sample items */

  Item i1("A big sword", 5);
  Item i2("Some armor", 10);
  Item i3("fish", 1);
  Item i4("gold", 100);
  Item i5("potion", 30);

  /* add the items to the monster's inventory */
  m1.add_item(i1);
  m1.add_item(i4);
  m2.add_item(i2);
  m3.add_item(i3);
  m4.add_item(i4);
  m4.add_item(i3);
  m5.add_item(i5);
  m6.add_item(i4);
  /* The infastructure to support adding items to rooms  is there, but I'll skip it for now */

  /* create some sample rooms */

  Room r1("A cave");
  Room r2("The watchtower");
  Room r3("The courtyard");
  Room r4("The mess hall");
  Room r5("The library");
  Room r6("A dimly lit greenhouse");
  Room r7("The dungeons");
  Room r8("The dormitory");

  /* add the monsters to the rooms */
  r1.add_monster(m1);
  r2.add_monster(m3);
  r2.add_monster(m6);
  r3.add_monster(m2);
  r4.add_monster(m3);
  r5.add_monster(m4);
  r6.add_monster(m5);
  r6.add_monster(m1);
  r7.add_monster(m6);

  /* add to dungeon */
  dungeon->add_room(r1);
  dungeon->link(r1, r4, "south");
  dungeon->link(r1, r2, "east");
  dungeon->link(r1, r5, "southeast", true); //secret passageway

  dungeon->add_room(r2);
  dungeon->link(r2, r1, "west");
  dungeon->link(r2, r3, "east");
  dungeon->link(r2, r5, "south");
  dungeon->link(r2, r7, "far south");

  dungeon->add_room(r3);
  dungeon->link(r3, r5, "southwest");

  dungeon->add_room(r4);
  dungeon->link(r4, r5, "east");
  dungeon->link(r4, r6, "south");

  dungeon->add_room(r5);
  dungeon->link(r5, r7, "south");

  dungeon->add_room(r6);
  dungeon->link(r6, r1, "north");
  dungeon->link(r6, r7, "east");

  dungeon->add_room(r7);
  dungeon->link(r7, r8, "east");
  dungeon->add_room(r8);

}

void Manager::print_usage() {
  cout << "Main Menu:" << endl;
  cout << "s -- start the game" << endl;
  cout << "l -- list inventory" << endl;
  cout << "d -- drop an item" << endl;
  cout << "n -- finish turn and move on to next player" << endl;
  cout << "q -- quit" << endl;
}

/* private methods */

char Manager::get_selection() {
  char a;
  cout << endl;
  cout << "Selection: ";
  cin >> a;
  cin.ignore(100, '\n');
  return a;
}

void Manager::add_player() {
  char name[50];
  cout << "new player name?" << endl;
  cin.getline(name, 50, '\n');
  cout << "what kind of player would you like to be? k for knight, a for archer, or w for wizard" << endl;
  Player *n_player = NULL;
  switch(get_selection()) {
    case 'k':
      n_player = new Knight(name, 100); 
      break;
    case 'a':
      n_player = new Archer(name, 75);
      break; 
    case 'w':
      n_player = new Wizard(name, 50);
      break;
    default:
      break;
  }
  players->add_player(*n_player);
  if (n_player)
    delete n_player;
}

void Manager::start(Player *p) {
  dungeon->start(*p);
}

void Manager::drop(Player &p) {
  char item_to_drop[50]; 
  int val;
  cout << "Name of item?" << endl;
  cin.clear();
  cin.getline(item_to_drop, 50, '\n');

  cout << "Item value?" << endl;
  cin >> val;

  Item i(item_to_drop, val);
  p.remove_item(i); 
}
