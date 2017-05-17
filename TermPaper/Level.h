#pragma once
#include <string>
#include <vector>
#include <list>
#include "LevelStorage.h"
#include "LevelBox.h"
#include "Player.h"
#include "ContactListener.h"
#include "TinyXML\tinyxml2.h"

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
	Storage storage;
	Player* player;
	b2World* level_world;
	MyContactListener* my_contact_listener_ptr;
	std::vector <std::string> images;
	void loadMap(tinyxml2::XMLElement *map);
	void loadObjects(tinyxml2::XMLElement *map);
	void loadObject(tinyxml2::XMLElement *objectgroup, BodyType b_type);
	void parsePlatform(tinyxml2::XMLElement *object, tinyxml2::XMLElement * objectgroup, b2Body* body);
	void parseSensor(tinyxml2::XMLElement *object, b2Body* body, std::vector<Action> stages);
	void parseTimer(tinyxml2::XMLElement *object, std::vector<Action> stages);
	void parseBridge(tinyxml2::XMLElement *object, b2Body* body, b2BodyDef* body_def, Object* tmp_obj);
	std::vector<Action> sensorStagesParser(std::vector<std::string> stages);
	tinyxml2::XMLElement * findAmongSiblings(tinyxml2::XMLElement * element, std::string name);
	std::vector<std::string> stringDelimiter(std::string init_str);
	std::vector<std::pair<double, double>> buildTrajectory(tinyxml2::XMLElement * objectgroup, std::string trajectory_name, bool* is_rounded);
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
