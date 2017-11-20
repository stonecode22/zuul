#include<iostream>
#include<vector>
#include "room.h"
using namespace std;

#define location 1
#define exit 2
#define move 3
#define pickup 4
#define drop 5

int command(char* choice);
void goto_room(Room* &current_room);
bool item_inside(char * item_id, vector<item*> inventory);
void pickup(Room* &current_room, vector<item*> &inventory);
item* drop_location(char* item_id, vector<item*> &inventory);
void drop(Room* &current_room, vector<item*> &inventory);

int main()
{
  vector<Room*> rooms;
  vector<item*> inventory;
  bool finish = false;

  cout << "You're stuck in a ..." << endl;
  cout << "This is the chance you've been waiting for. You have to escape." << endl;

  //initialization of all rooms
  Room* cell_1 = new Room((char*) "Cell #761", (char*) "You've awakened in your dusty cell from the loud noises outside. The cell door is unlocked. You contemplate escaping... not like you have much of a choice.");

  cell_1->set_exit(0, walkarea);
