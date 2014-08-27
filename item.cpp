#include "item.h"

/* initializes Item's members */
Item::Item() {
  name = NULL;
  value = 0;
}

/* alternative constructor, calls helper function */
Item::Item(const char *description, int val) {
  create_item(description, val);
}

/* deallocates any memory Item may have created with new */
Item::~Item() {
  delete[] name;
  value = 0;
}

/* copy constructor, calls the helper function */
Item::Item(const Item &other) {
  create_item(other.name, other.value);
}

void Item::display() {
  cout << "Item: " << name;
  cout << " (value = " << value << ")" << endl;
}

/* overloaded operator to check it two items are the same. */
/* Items are the same if they have the same name and their values are equal */
bool Item::operator==(Item &other) {
  return (strcmp(name, other.name) == 0 && other.value == value) ? true : false;
}

/* private function to create a new item from a given description and value */
void Item::create_item(const char *description, int val) {
  if (description) {
    name = new char[strlen(description) + 1];
    strcpy(name, description);
  }
  value = val;
}

/* Node stuff */

Node::Node() {
  next = NULL;
  prev = NULL;
}

Node::~Node() {
  next = NULL;
  prev = NULL;
}

/* call Item's constructor with an init. list */
Node::Node(const Item &other) : Item(other) {
}

Node *&Node::next_item() {
  return next;
}

Node *&Node::prev_item() {
  return prev;
}

void Node::connectNext(Node *other) {
  next = other;
}

void Node::connectPrev(Node *other) {
  prev = other;
}
