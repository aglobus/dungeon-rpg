#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>

using namespace std;

class Item {
  public:
    Item();
    Item(const char *, int);
    ~Item();
    Item(const Item &);
    void display();
    bool operator==(Item &);
  protected:
    char *name;
    int value;
  private:
    void create_item(const char *, int);
};

/* wrapper for an Item */
/* A node is an Item, plus the extra stuff that makes it useful for operations we need for the Inventory DLL */
class Node : public Item {
  public:
    Node();
    ~Node();
    Node(const Item &);
    Node *& next_item();
    Node *& prev_item();
    void connectNext(Node *);
    void connectPrev(Node *);
  private:
    Node *next;
    Node *prev;
};
#endif
