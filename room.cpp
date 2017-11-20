#include<iostream>
#include<string.h>
#include<map>
#include<vector>
#include "room.h"
using namespace std;

//constructor
Room::Room(char* new_id, char* new_desc)
{
  id = new_id;
  desc = new_desc;
}

char* Room::get_id()
{
  return id;
}

char* Room::get_desc()
{
  return desc;
}

void Room::set_exit(int direction, Room* next_room)
{
  exitMap[direction] = next_room;
}

Room *Room::get_exit(int exit)
{
  map<int, Room*>::iterator it;
  it = exitMap.find(exit);

  if(it != exitMap.end())
    {
      return exitMap.find(exit)->second;
    }
  else
    {
      return 0;
    }
}

void Room:: add_item(item* new_item)
{
  inv.push_back(new_item);
}

item* Room::drop_item(char* item_id)
{
  for(int i = 0; i < inv.size(); i++)
    {
      if(!strcmp(item_id, inv.at(i)->id))
	{
	  item* get_item = inv.at(i);
	  inv.erase(inv.begin() + i);
	  return get_item;
	}
    }
  return 0;
}

bool Room::room_items()
{
  if(inv.empty())
    {
      return false;
    }
  else
    {
      return true;
    }
}

