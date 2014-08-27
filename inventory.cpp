#include "inventory.h"

Inventory::Inventory() {
  head = NULL;
  tail = NULL;
  n_items = 0;
}

Inventory::~Inventory() {
  /* completely kill the DLL */
  remove_all();
}

Inventory::Inventory(const Inventory &other) {
  head = NULL;
  tail = NULL;
  /* copy the over inventory into ours */
  copy_inventory(other);
}

Inventory &Inventory::operator=(const Inventory &other) {
  copy_inventory(other);
  return *this;
}

void Inventory::add_item(Item &to_add) {
  /* add to DLL */
  if (!head) {
    head = new Node(to_add);
    tail = head;
    n_items++;
    return;
  }
  Node *n = new Node(to_add);
  n->connectNext(head);
  head->connectPrev(n);
  head = n;
  n_items++;
  return;
}

/* recursive wrapper */
void Inventory::remove_item(Item &to_remove) {
  remove_item(to_remove, head);
}

void Inventory::remove_item(Item &to_remove, Node *current) {
  if (!current)
    return;
  if (*current == to_remove) {
    if (*current == *tail)
      tail = current->prev_item();
    if (*current == *head)
      head = current->next_item();
    if (current->next_item())
      current->next_item()->connectPrev(current->prev_item());
    if (current->prev_item())
      current->prev_item()->connectNext(current->next_item());
    delete current;
    current = NULL;
    n_items--;
    return;
  }
  remove_item(to_remove, current->next_item());
}

void Inventory::remove_all() {
  Node *current = head;
  for (;current != NULL; current = current->next_item()) {
    if (current->prev_item())
      delete current->prev_item();
  }
  delete tail;

  head = NULL;
  tail = NULL;
  n_items = 0;
}

void Inventory::display() {
  Node *current = head;
  //cout << "Total Items in our inventory: " << n_items << endl;
  while (current) {
    current->display();
    current = current->next_item();
  }
}

void Inventory::copy_inventory(const Inventory &other) {
  Node *current = other.head;
  while (current) {
    add_item(*current);
    current = current->next_item();
  }
  n_items = other.n_items;
}

void Inventory::copy_inventory(const Inventory &other, Item &filter) {
  Node *current = other.head;
  while (current) {
    if (*current == filter)
      add_item(*current);
    current = current->next_item();
  }
  n_items = other.n_items;
}

int Inventory::get_n_items() {
  return n_items;
}
