#include "room.h"

/* Room Class */

Room::Room() : num_monsters(0), head(NULL), description(NULL) {
  monsters = new Monster*[MAXMONSTERS];
  for (int i = 0; i < MAXMONSTERS; i++)
    monsters[i] = NULL;
}

Room::Room(char *room_description) : head(NULL), num_monsters(0) {
  create_room(room_description);
  monsters = new Monster*[MAXMONSTERS];
  for (int i = 0; i < MAXMONSTERS; i++)
    monsters[i] = NULL;
}

Room::~Room() {
  delete[] monsters; 
  monsters = NULL;
  delete[] description;
  description = NULL;
  num_monsters = 0;
  /* delete LLL of rooms */
  unlink_all();
}

Room::Room(const Room &other) : Inventory(other) {
  copy_room(other);
}

Room &Room::operator=(const Room &other) {
  copy_room(other); //copy the room wrapper
  Inventory::operator=(other); //copy the inherited stuff
  return *this;
}

bool Room::operator==(const Room &compare) {
  //rooms will be considered the same if they have the same description, regardless of monsters or inventory in the room
  //maybe change this later to be more comprehensive
  return (strcmp(compare.description, description) == 0) ? true : false; 
}

void Room::display() {
  cout << "---" << endl;
  cout << "Room description: " << description << endl;
  cout << "Room inventory: " << endl;
  Inventory::display();
  /* for each monster, display */
  if (monsters) {
    cout << "# monsters here: " << num_monsters << endl;
    for (int i = 0; i < num_monsters; i++)
      monsters[i]->display();
  }
  cout << "---" << endl;
}

void Room::display_adjacent() {
  cout << "Adjacent Rooms:" << endl << endl;
  print(head);
}

int Room::add_monster(Monster &to_add) {
  if (num_monsters >= MAXMONSTERS) 
    return 0;
  monsters[num_monsters] = new Monster(to_add);
  //*monsters[num_monsters] = to_add;
  num_monsters++;
  return 1;
}

void Room::link(Room &connect_to, char *d, bool secret) {
  head = insert(connect_to, head, d, secret);
}

void Room::unlink(Room &to_remove) {
  head = remove(to_remove, head);
}

void Room::unlink_all() {
  Hall *current = head;
  Hall *next;
  while (current) {
    next = current->get_next();
    delete current;
    current = next;
  }
  head = NULL;
}
/* ptr to next room */
Room* Room::fight(Player &p) {
  display();
  /* loop through monsters and fight each one */
  if (!*monsters) {
    return NULL;
  }
  for (int i = 0; monsters[i]; i++) {
    while (monsters[i]->attack() != 0)
      cout << "Incorrect! Try again!" << endl;

    cout << "monster defeated! Looting!" << endl;
    //p.copy_inventory(*monsters[i]);
    
    /* power of polymorphism here, calls loot() of the object type */
    p.loot(*monsters[i]);
    monsters[i]->remove_all(); //remove it from the monster's inventory

    cout << "here's our loot so far: " << endl;
    p.Inventory::display();
  }
  display_adjacent();
  /* ask where we'd like to go next */
  cout << "enter a direction to go to next" << endl;
  char new_direction[20];
  Room *next = NULL;
  do {
    cin.clear();
    cin.getline(new_direction, 50, '\n');
    next = retrieve(new_direction, head);
    if (next) {
      return next;
    }
  } while (true);
  return NULL;
}

bool Room::is_solo() {
  return (!head) ? true : false;
}

/* private */

/* LLL copy */
Hall *Room::copy(Hall *current) {
  if (!current)
    return NULL;
  Hall *new_copy = new Hall(*current);
  new_copy->connect_next(copy(current->get_next()));
  return new_copy; // returns the head of the freshly copied LLL
}

/* copies the data from one Room into this one */
/* just handle the data members of this class, the initialization list should take care of the inherited stuff */
void Room::copy_room(const Room &other) {
  /* desc */
  if (description)
    delete[] description; //get rid of whatever description we have
  create_room(other.description);  //set the room description to other.description
  /* num_monsters */
  num_monsters = other.num_monsters;
  /* list */
  head = copy(other.head); //copy over the other LLL of adjacent rooms
  /* monsters */
  if (other.monsters)
    delete[] monsters; 
  monsters = new Monster*[MAXMONSTERS];
  for (int i = 0; other.monsters[i]; i++) //possible segfault
    monsters[i] = new Monster(*other.monsters[i]);
}

void Room::create_room(char *desc) {
  if (desc) {
    description = new char[strlen(desc) + 1];
    strcpy(description, desc);
  }
}

/* recursively append Hall to LL, returns pointer to head of list */
/* pushing in front would be faster */
Hall *Room::insert(Room &connect_to, Hall *context, char *dir, bool sec) {
  if (!context) {
    Hall *tmp = new Hall(connect_to);
    tmp->set_direction(dir);
    tmp->set_secret(sec);
    return tmp;
  }
  context->connect_next(insert(connect_to, context->get_next(), dir, sec)); 
  return context;
}


Hall *Room::remove(Room &to_kill, Hall *context) {
  if (!context)
    return NULL;

  if (to_kill == *context) {
    Hall *tmp = context->get_next();
    delete context;
    return tmp;
  }
  context->connect_next(remove(to_kill, context->get_next())); 
  return context;
}

Hall *Room::retrieve(char *direc, Hall *context) {
  if (!context)
    return NULL;

  if (context->compare_direction(direc)) {
    return context;
  }
  return retrieve(direc, context->get_next());
}

void Room::print(Hall *context) {
  if (!context)
    return;
  if (context->display()) {
    cout << "Direction to get to above room: " << context->get_direction() << endl;
    cout << endl;
  }
  print(context->get_next());
}

/* Hall Class */

Hall::Hall() {
  direction = NULL;
  secret = false;
}

Hall::~Hall() {
  if (direction)
    delete[] direction;
  next = NULL;
}

Hall::Hall(const Hall &other) : Room(other), secret(other.secret) {
  if (other.direction) {
    set_direction(other.direction);
  }
}

Hall::Hall(const Room &other) : Room(other), next(NULL), secret(false)  {
}

bool Hall::operator==(const Hall &other) {
  return Room::operator==(other);
}

Hall *&Hall::get_next() {
  return next;
}

char *Hall::get_direction() {
  return direction;
}

void Hall::set_direction(char *new_dir) {
  if (direction)
    delete[] direction;
  direction = new char[strlen(new_dir) + 1];
  strcpy(direction, new_dir);
}

void Hall::set_secret(bool n) {
  secret = n;
}

void Hall::connect_next(Hall *connect_to) {
  next = connect_to; //connect_to should point to another DA Hall
}

bool Hall::compare_direction(char *d) {
  return (strcmp(d, direction) == 0) ? true : false;
}

bool Hall::display() {
  if (!secret) {
    Room::display();
    return true;
  }
  return false;
}
