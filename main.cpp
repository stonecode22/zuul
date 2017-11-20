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

  cout << "Tomorrow is your last day. Guilty of a murder you did not do, you are put in death row. The arrangements have been made for your execution tomorrow morning. You go to sleep, only to be haunted by nightmares. You are determined to have your last rest be the most peaceful. However, your rest abruptly ended when you heard a loud noise near your cell. It took you a couple of minutes to come to your senses, but you looked around your cell to be met with an open cell door. The lock was on the ground, broken in shards, like someone was hammering through it. You peek outside and look in both directions. No one is there. The clock in your cell read: 4:30AM. Everyone must still be sleeping. You wonder about who broke the lock for you, but you decide that it wasn't important. You contemplate escaping." << endl;
  cout << endl << "This is the chance you've been waiting for. You have to escape." << endl;

  //initialization of all rooms
  Room* cell_1 = new Room((char*) "Cell #761", (char*) "Home sweet home. You see the bed you've slept in for the last 3 years with the fun activities that consisted of: staring at walls, floors, and ceilings.");
  Room* cell_2 = new Room((char*) "Cell #760", (char*) "You see your neighboring cellmate. You realize you still don't know his name.");
  Room* cell_3 = new Room((char*) "Cell #762", (char*) "You see an empty cell. The previous inhabitant of that cell disappeared from his cell a week ago. No one has occupied the cell since.");
  Room* gate_entry = new Room((char*) "Gate Entrance", (char*) "You see a metal door. What lies beyond is unknown. You need a key to open it.");
  Room* gate_closet = new Room((char*) "Gate Entrance: Closet", (char*) "You see many empty, leftover cardboard boxes. Next to them are yardworking tools.");
  Room* visiting_area = new Room((char*) "Visiting Area", (char*) "You see several rows of windows and chairs. Prisoners come here to talk with people from the outside world.");
  Room* west_exit = new Room((char*) "West Exit", (char*) "You alter the shape of the paperclip and use it as a key. After a few moments, the doorknob clicks. You have escaped!");
  Room* offices= new Room((char*) "Offices", (char*) "You see desks and large stacks of paper. This must be where the wardens sit down and do paperwork. No one is here, but you hear loud chatter behind the door to the next room.");
  Room* guard_room = new Room((char*) "Guard Room", (char*) "You see that you have done messed up. The room is full of guards. Rip.");
  Room* east_exit = new Room((char*) "West Exit", (char*) "The guards didn't notice you through your disguise. You have escaped!");
  Room* cafe = new Room((char*) "Cafeteria", (char*) "You see the ordered tables with leftover food on the surfaces. Most of it has expired.");
  Room* hygiene = new Room((char*) "Bathroom", (char*) "You see organized and plain showers and stalls. Everything looks in place except the mirror in the far corner. It's loosely screwed to the wall");
  Room* north_exit = new Room((char*) "North Exit", (char*) "You use the screwdriver to unscrew the mirror. Ahead lies a tunnel with a makeshift ladder. Someone must have escaped using this before. You see light ahead. You have escaped!");
  Room* rec_area = new Room((char*) "Recreational Area", (char*) "You see a soccer field and pull-up bars. You also notice that the soil is weakly formed alongside the gates.");
  Room* south_exit = new Room((char*) "South Exit", (char*) "You've successfully dug out and see the jailhouse behind you. You have escaped!");
  Room* classroom_main = new Room((char*) "Classroom", (char*) "You see a large whiteboard with seats pointed towards it. It writes: 'You cannot escape your problems!' Hopefully that isn't true.");
  Room* classroom_front = new Room((char*) "Classroom: Front Desk", (char*) "You come close to the desk near the whiteboard. One of the drawers is unlocked.");
  Room* classroom_office = new Room((char*) "Classroom: Teacher's Office", (char*) "You see a giant desk with the teacher looking at you. He presses the alarm and you are busted.");
  Room* classroom_closet = new Room((char*) "Classroom: Closet", (char*) "You see a box of supplies within the closet after wiping away the dust. The woodshopping tools from the last unit are still there.");
  Room*
  

    //navigation uses/setting exits
    //set_exit(x, room), x is a number between 0-3, 0 = N, 1 = E, 2 = S, 3 = W
  cell_1->set_exit(0, cell_2);
  cell_1->set_exit(2, cell_3);
  cell_2->set_exit(0, gate_entry);
  cell_2->set_exit(2, cell_1);
  cell_3->set_exit(0, cell_1);
  cell_3->set_exit(1, cafe);
  gate_entry->set_exit(2, cell_2);
  gate_entry->set_exit(1, gate_closet);
  gate_entry->set_exit(0, visting_area);
  gate_closet->set_exit(3, gate_entry);
  visiting_area->set_exit(3, west_exit);
  visiting_area->set_exit(2, gate_entry);
  visiting_area->set_exit(1, offices);
  offices->set_exit(1, guard_room);
  offices->set_exit(3, visting_room);
  guard_room->set_exit(3, offices);
  guard_room->set_exit(1, east_exit);
  cafe->set_exit(3, cell_3);
  cafe->set_exit(0, hygiene);
  cafe->set_exit(1, classroom_main);
  cafe->set_exit(2, rec_area);
  rec_area->set_exit(2, south_exit);
  rec_area->set_exit(0, cafe);
  hygiene->set_exit(2, cafe);
  hygiene->set_exit(0, north_exit);
  classroom_main->set_exit(3, cafe);
  classroom_main->set_exit(0, classroom_front);
  classroom_main->set_exit(1, classroom_closet);
  classroom_front->set_exit(2, classroom_main);
  classroom_front->set_exit(1, classroom_office);
  classroom_closet->set_exit(3, classroom_main);
  
  
  
  
  
