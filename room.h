#include<iostream>
#include<string.h>
#include<vector>
#include<map>
using namespace std;

struct item
{
  char* id;
};

class Room
{
 public:
  Room(char* , char*);
  char* get_id();
  char* get_desc();
  void set_exit(int direction, Room* next_room);
  Room* get_exit(int exit);
  void add_item(item* new_item);
  item* drop_item(char* item_id);
  bool room_items();
  vector<item*> inventory;
  
 private:
  char* id;
  char* desc;
  map<int, Room*> exitMap;
};
