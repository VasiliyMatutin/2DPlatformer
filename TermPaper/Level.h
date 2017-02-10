#pragma once
#include <string>
#include <vector>
#include "LevelBox.h"
#include "DynamicObj.h"
#include "ContactListener.h"

class Level
{
	int level_width, level_height, tile_width, tile_height;
	std::vector<Object> unchangeable_objects;
	std::vector<Object> changeable_objects;
	DynamicObj* player;
	b2World* level_world;
	MyContactListener* my_contact_listener_ptr;
	std::vector <std::string> images;
public:
	Level();
	~Level();
	bool loadLevel(std::string filename);
	std::vector<Object>& getUnchangeableObjectList();
	std::vector<Object>& getChangeableObjectList();
	std::vector<std::string>& getImagesList();
	DynamicObj* returnActivePlayer();
	void update();
};
