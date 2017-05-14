#pragma once
#include <string>
#include <vector>
#include <list>
#include <map>
#include "LevelBox.h"
#include "Player.h"
#include "Platform.h"
#include "ContactListener.h"
#include "ManualSwitchObj.h"
#include "VisibleSensor.h"
#include "Lever.h"
#include "Timer.h"
#include "tinyxml2.h"

enum class BodyType
{
	STATIC,
	KINEMATIC,
	DYNAMIC,
	SENSOR
};

class Level
{
	int level_width, level_height, tile_width, tile_height;
	std::list<Object> unchangeable_objects;
	std::list<Object> changeable_objects;
	Player* player;
	std::list<Platform*> platform_list;
	std::list<Lever*> lever_list;
	std::list<Sensor*> sensor_list;
	std::list<Timer*> timer_list;
	std::list<NonStaticObj*> non_static_objects;
	std::map<std::string, ManualSwitchObj*> future_observables;
	b2World* level_world;
	MyContactListener* my_contact_listener_ptr;
	std::vector <std::string> images;
	tinyxml2::XMLElement * findAmongSiblings(tinyxml2::XMLElement * element, std::string name);
	std::vector<std::pair<double, double>> buildTrajectory(tinyxml2::XMLElement * objectgroup, std::string trajectory_name, bool* is_rounded);
	void loadMap(tinyxml2::XMLElement *map);
	void loadObjects(tinyxml2::XMLElement *map);
	void loadObject(tinyxml2::XMLElement *objectgroup, BodyType b_type);
	void parseSensor(tinyxml2::XMLElement *object, b2Body* body);
	void parseTimer(tinyxml2::XMLElement *object);
public:
	Level();
	~Level();
	bool loadLevel(std::string filename);
	std::list<Object>& getUnchangeableObjectList();
	std::list<Object>& getChangeableObjectList();
	std::vector<std::string>& getImagesList();
	Player* returnActivePlayer();
	void tryToSwitchLever();
	void update();
};
