#include "inventory.h"
#include "monster.h"
#include "player.h"
#include "dungeon.h"

class Manager {
  public:
    Manager();
    ~Manager();
    Manager(const Manager &);
    void start();
    void create_sample_dungeon();
    void print_usage();
  private:
    /* data */
    Dungeon *dungeon;
    player_collection *players;
    /* methods */
    char get_selection();
    void add_player();
    void start(Player *);
    void drop(Player &);
};
