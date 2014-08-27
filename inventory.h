#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"

/* An inventory is implemented as a DLL */
/* Every class has an inventory (technically IS an inventory) */
class Inventory {
  public:
    Inventory();
    ~Inventory();
    Inventory(const Inventory &);
    Inventory &operator=(const Inventory &);

    void add_item(Item &); //add item to DLL
    void remove_item(Item &); // remove item from DLL
    void remove_all(); //remove all items from DLL
    void display(); //display DLL
    void copy_inventory(const Inventory &); //copy another DLL into this one
    void copy_inventory(const Inventory &, Item &);
    int get_n_items(); //return # of items in our inventory
  private:
    Node *head;
    Node *tail;
    int n_items; //current number of items

    void remove_item(Item &, Node *);
};

#endif
