#pragma once
#include <string>
#include <vector>
#include <list>
#include "LevelBox.h"
#include "Player.h"
#include "ContactListener.h"

class Level
{
	int level_width, level_height, tile_width, tile_height;
	std::list<Object> unchangeable_objects;
	std::list<Object> changeable_objects;
	Player* player;
	b2World* level_world;
	MyContactListener* my_contact_listener_ptr;
	std::vector <std::string> images;
public:
	Level();
	~Level();
	bool loadLevel(std::string filename);
	std::list<Object>& getUnchangeableObjectList();
	std::list<Object>& getChangeableObjectList();
	std::vector<std::string>& getImagesList();
	Player* returnActivePlayer();
	void update();
};
