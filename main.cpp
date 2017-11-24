/*Zuul By Stone Yang
/An adventure game where the main character is stuck in a prison, struggling to get out.
/The player must find items to win/unlock conditions in order to win
/The player has 3 loss conditions (getting caught by guards) and 4 win conditions (escape!)
/z
/
/
/
*/
#include<iostream>
#include<vector>
#include "room.h"
using namespace std;

#define LOCATION 1
#define MOVE 2
#define EXITS 3
#define PICKUP 4
#define DROP 5

int nav_command(char* choice);
void goto_room(Room* &current_room, vector<item*> &inventory);
bool have_item(char * item_id, vector<item*> inventory);
void pickup(Room* &current_room, vector<item*> &inventory);
item* drop_location(char* item_id, vector<item*> &inventory);
void drop(Room* &current_room, vector<item*> &inventory);

int main()
{
  vector<Room*> rooms;
  vector<item*> inventory;
  bool finish = false;
  char nope;
  
  //random & long storyline of a prisoner
  cout << "Tomorrow is your last day. Guilty of a murder you did not do, you are put in death row. The arrangements have been made for your execution tomorrow morning. You go to sleep, only to be haunted by nightmares. You are determined to have your last rest be the most peaceful. However, your rest abruptly ends when you hear a loud noise outside. It takes you a couple of minutes to come to your senses, but you look around your cell and notice an open cell door. The lock was on the ground, broken in shards, like someone was hammering through it. You peek outside and look in both directions. No one is there. The clock in your cell read: 4:30AM. Everyone must still be sleeping. You wonder about who broke the lock for you, but you decide that it wasn't important. You contemplate escaping." << endl;
  cout << "Do you want to escape? (Y/Y)" << endl;
  cin >> nope;
  if(nope != 'Y')
    {
      cout << "Well, too bad." << endl;
    }
  cout << endl << "This is the chance you've been waiting for. You have to escape." << endl;

  //initialization of all rooms & descriptions
  Room* cell_1 = new Room((char*) "Cell #761", (char*) "Home sweet home.");
  Room* cell_2 = new Room((char*) "Cell #760", (char*) "You see your neighboring cellmate. You still don't know his name.");
  Room* cell_3 = new Room((char*) "Cell #762", (char*) "You see an empty cell. One of the drawers are left open.");
  Room* gate_entry = new Room((char*) "Gate Entrance", (char*) "You see a metal door. What lies beyond is unknown.");
  Room* gate_closet = new Room((char*) "Gate Entrance: Closet", (char*) "You see many empty, leftover cardboard boxes. Next to them are yardworking tools.");
  Room* visiting_area = new Room((char*) "Visiting Area", (char*) "You see several rows of windows and chairs. Prisoners come here to talk with people from the outside world.");
  Room* west_exit = new Room((char*) "West Exit", (char*) "You alter the shape of the paperclip and use it as a key. After a few moments, the doorknob clicks. You smell the freedom.");
  Room* offices= new Room((char*) "Offices", (char*) "You see desks and large stacks of paper. This must be where the wardens sit down and do paperwork. No one is here, but you hear loud chatter behind the door to the next room.");
  Room* guard_room = new Room((char*) "Guard Room", (char*) "The room is full of guards. They notice you coming in.");
  Room* east_exit = new Room((char*) "East Exit", (char*) "You sneak past the guards with your disguise. As you open the door, you see the light of freedom.");
  Room* cafe = new Room((char*) "Cafeteria", (char*) "You see the ordered tables with leftover food on the surfaces. Most of it has expired.");
  Room* hygiene = new Room((char*) "Bathroom", (char*) "You see organized and plain showers and stalls. Everything looks in place except the loosely screwed-in mirror in the far corner.");
  Room* north_exit = new Room((char*) "Suspicious Mirror", (char*) "You use the screwdriver to unscrew the mirror. Ahead lies a tunnel with a makeshift ladder. Someone must have escaped using this before. You see the light of freedom ahead.");
  Room* rec_area = new Room((char*) "Recreational Area", (char*) "You see a soccer field and pull-up bars. You also notice that the soil is weakly formed alongside the gates.");
  Room* south_exit = new Room((char*) "Suspicious Pile of Dirt", (char*) "You've successfully dug out and see the jailhouse behind you. You smell the freedom.");
  Room* classroom_main = new Room((char*) "Classroom", (char*) "You see a large whiteboard with seats pointed towards it. It writes: 'You cannot escape your problems!' Hopefully that isn't true.");
  Room* classroom_front = new Room((char*) "Classroom: Front Desk", (char*) "You come close to the desk near the whiteboard. One of the drawers is unlocked. You also hear noises towards the East.");
  Room* classroom_office = new Room((char*) "Classroom: Teacher's Office", (char*) "You see the teacher talking to one of the guards. They notice you.");
  Room* classroom_closet = new Room((char*) "Classroom: Closet", (char*) "You see a box of supplies within the closet after wiping away the dust. The woodshopping tools from the last unit are still there.");
  
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
  gate_entry->set_exit(0, visiting_area);
  gate_closet->set_exit(3, gate_entry);
  visiting_area->set_exit(3, west_exit);
  visiting_area->set_exit(2, gate_entry);
  visiting_area->set_exit(1, offices);
  offices->set_exit(1, guard_room);
  offices->set_exit(3, visiting_area);
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
  classroom_office->set_exit(3, classroom_front);

  //Setting up the items
  item* key = new item();
  item* paperclip = new item();
  item* uniform = new item();
  item* shovel = new item();
  item* screwdriver = new item();
  
  //Naming the items
  key->id = (char*)"Key";
  paperclip->id = (char*) "Paperclip";
  uniform->id = (char*) "Uniform";
  shovel->id = (char*) "Shovel";
  screwdriver->id = (char*) "Screwdriver";
  
  //Setting initial location of the items
  classroom_front->add_item(key);
  cell_3->add_item(paperclip);
  hygiene->add_item(uniform);
  gate_closet->add_item(shovel);
  classroom_closet->add_item(screwdriver);

  //Adds rooms to vector
  rooms.push_back(cell_1);
  rooms.push_back(cell_2);
  rooms.push_back(cell_3);
  rooms.push_back(gate_entry);
  rooms.push_back(gate_closet);
  rooms.push_back(visiting_area);
  rooms.push_back(offices);
  rooms.push_back(guard_room);
  rooms.push_back(cafe);
  rooms.push_back(rec_area);
  rooms.push_back(hygiene);
  rooms.push_back(classroom_main);
  rooms.push_back(classroom_front);
  rooms.push_back(classroom_closet);
  rooms.push_back(classroom_office);
  rooms.push_back(north_exit);
  rooms.push_back(east_exit);
  rooms.push_back(south_exit);
  rooms.push_back(west_exit);

  int timer = 0;
  Room* current_room = cell_1; //Starting point of the game
  cout << current_room->get_desc() << endl;
  while(!finish)
    {
      //Win & loss conditions
      if(timer >= 30) //Loss condition #1: Move 30 times without winning
	{
	  cout << "You ran into a guard! It looks like you took too long. Death row awaits. Bad End 1/3 (Hint: Don't make unnecessary movements!)" << endl;
	  break;
	}
      
      if(current_room->get_exit(1) != 0) //Loss Condition #2: Go into the Guard Room without a Uniform
	{
	  if(!strcmp(current_room->get_id(), "Guard Room") && !have_item((char*)"Uniform", inventory))
	    {
	      cout << "You ran into a guard! Death row awaits. Bad End 2/3 (Hint: Get a Uniform!)" << endl;
	      break;
	    }
	}
      
      if(current_room->get_exit(3) != 0) //Loss Condition #3: Go into the Teacher's Office without a Uniform
	{
	  if(!strcmp(current_room->get_id(), "Classroom: Teacher's Office") && !have_item((char*)"Uniform", inventory))
	    {
	      cout << "You ran into a guard! Death row awaits. Bad End 3/3 (Hint: Get a Uniform!)" << endl;
	      break;
	    }
	}      
      
      if(!strcmp(current_room->get_id(), "Suspicious Mirror")) //Win condition #1: Unscrew the Mirror (requires "Screwdriver")
	{
	  cout << "You have escaped! (North Exit: Good End 1/4)" << endl;
	  break;
	}
      if(!strcmp(current_room->get_id(), "East Exit")) //Win condition #2: Get to the East Exit (requires "Uniform") 
	{
	  cout << "You have escaped! (East Exit: Good End 2/4)" << endl;
	  break;
	}
      if(!strcmp(current_room->get_id(), "Suspicious Pile of Dirt")) //Win condition #3: Dig out of jail (requires "Shovel")
	{
	  cout << "You have escaped! (South Exit: Good End 3/4)" << endl;
	  break;
	}
      if(!strcmp(current_room->get_id(), "West Exit")) //Win condition #4: Lockpick the door (requires "Paperclip")
	{
	  cout << "You have escaped! (West Exit: Good End 4/4)" << endl;
	  break;
	}
      
      cout << "Navigator online. Commands: LOCATION, MOVE, EXITS, PICKUP, DROP." << endl; //Reads user-inputted commands
      char* choice = new char[10];
      cin >> choice;

      switch(nav_command(choice))
	{
	case LOCATION: //Prints current location
	  cout << current_room->get_id() << endl;
	  break;
	  
	case MOVE: //Prompts travelling menu
	  goto_room(current_room, inventory);
	  cout << current_room->get_id();
	  cout << ": " << current_room->get_desc() << endl;
	  timer++;
	  break;
	      
	case EXITS: //Prints exits for the current room
	  cout << "Here's what I've found: " << endl;
	  for(int i = 0; i < 4; i++)
	    {
	      switch(i)
		{
		case 0:
		  cout << "North: ";
		  break;
		case 1:
		  cout << "East: ";
		  break;
		case 2:
		  cout << "South: ";
		  break;
		case 3:
		  cout << "West: ";
		  break;
		}
	      if(current_room->get_exit(i) != 0)
		{
		  cout << current_room->get_exit(i)->get_id() << endl;
		}
	      else
		{
		  cout << endl;
		}
	    }
	  break;
	  
	case PICKUP: //Pickup items in a room (if there are any)
	  pickup(current_room, inventory);
	  break;

	case DROP: //Drop items from inventory
	  drop(current_room, inventory);
	  break;

	default: //If none of the above, print Invalid command
	  cout << "Invalid command." << endl;
	  
	}
    }
  return 0;
}

int nav_command(char* choice) //Navigator function that returns values by command
{
  for(int i = 0; i < strlen(choice); i++)
    {
      choice[i] = toupper(choice[i]);
    }
  if(!strcmp(choice, "LOCATION"))
    {
      return LOCATION;
    }
  else if(!strcmp(choice, "MOVE"))
    {
      return MOVE;
    }
  else if(!strcmp(choice, "EXITS"))
    {
      return EXITS;
    }
  else if(!strcmp(choice, "PICKUP"))
    {
      return PICKUP;
    }
  else if(!strcmp(choice, "DROP"))
    {
      return DROP;
    }
  else
    {
      return 0;
    }
}

void goto_room(Room* &current_room, vector<item*> &inventory) //Using "MOVE" to read user-input in which room to go (from one of the exits)
{
  char input[10];
  cout << "Where do you want to go? (N, E, S, W) " << endl;
  cin >> input;

  if(!strcmp(input, "N") && !strcmp(current_room->get_id(), "Gate Entrance") && !have_item((char*)"Key", inventory)) //Prevents user from moving to the Visiting Area without a Key
    {
      cout << "The gate won't open. You need a key." << endl;
    }
  else if(!strcmp(input, "N") && !strcmp(current_room->get_id(), "Bathroom") && !have_item((char*)"Screwdriver", inventory)) //"   " to the North Exit without a Screwdriver
    {
      cout << "The mirror won't come off. You need some sort of tool to remove the screws." << endl;
    }
  else if(!strcmp(input, "S") && !strcmp(current_room->get_id(), "Recreational Area") && !have_item((char*)"Shovel", inventory)) //"   " to the South Exit without a Shovel
    {
      cout << "The dirt is too thick to dig with your hands. You need a shovel." << endl;
    }
  else if(!strcmp(input, "W") && !strcmp(current_room->get_id(), "Visiting Area") && !have_item((char*)"Paperclip", inventory)) //"   " to the West Exit without a Paperclip
    {
      cout << "The door won't open. The Gate Key doesn't work. You need another key." << endl;
    }
  else if(!strcmp(input, "N")) //Regular commands in moving to a different room that has no restrictions
    {
      current_room = current_room->get_exit(0);
    }
  else if(!strcmp(input, "E"))
    {
      current_room = current_room->get_exit(1);
    }
  else if(!strcmp(input, "S"))
    {
      current_room = current_room->get_exit(2);
    }
  else if(!strcmp(input, "W"))
    {
      current_room = current_room->get_exit(3);
    }
}

bool have_item(char* item_id, vector<item*> inventory) //Tests whether an item is in the user's inventory
{
  for(int i = 0; i < inventory.size(); i++)
    {
      if(!strcasecmp(item_id, inventory.at(i)->id))
	{
	  return true;
	}
    }
  return false;
}

void pickup(Room* &current_room, vector<item*> &inventory) //Pickup function
{
  if(current_room->room_items())
    {
      cout << "Navigator has found the item(s): " << endl;
      for(int i = 0; i < current_room->inv.size(); i++) //Using "PICKUP" to print items in the room
	{
	  cout << current_room->inv.at(i)->id << endl;
	}
      cout << "Enter the item you would like to pick up: ";
      char input[20];
      cin >> input;
      item* temp = new item();
      if((temp = current_room->drop_item(input)) != 0) //Picks up item from the room into the inventory
	{
	  inventory.push_back(temp);
	  return;
	}
      else
	{
	  cout << "The item does not exist!" << endl;
	  return;
	}
    }
  else
    {
      cout << "No items of use here." << endl; //If there are no items in the room
    }
}

item* drop_location(char* item_id, vector<item*> &inventory)
{
  for(int i = 0; i < inventory.size(); i++)
    {
      if(!strcasecmp(item_id, inventory.at(i)->id)) //Removes item from inventory
	{
	  item* rm_item = inventory.at(i);
	  inventory.erase(inventory.begin() + i);
	  return rm_item;
	}
    }
  return 0;
}

void drop(Room* &current_room, vector<item*> &inventory)
{
  cout << "Your inventory: " << endl;
  for(int i = 0; i < inventory.size(); i++)
    {
      cout << inventory.at(i)->id << endl;
    }
  cout << "What do you want to drop?" << endl;
  char input[20];
  cin >> input;
  item* temp = new item();
  if((temp = drop_location(input, inventory)) != 0) //Removes item from inventory using drop_location() and placing the item in the current room
    {
      current_room->inv.push_back(temp);
      return;
    }
  else
    {
      cout << "You don't have that item!" << endl; //If item doesn't exist in the inventory
    }
}
