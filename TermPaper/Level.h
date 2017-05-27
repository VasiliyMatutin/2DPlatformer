#pragma once
#include "LevelStorage.h"
#include "StrongPlayer.h"
#include "DexterousPlayer.h"
#include "ContactListener.h"
#include "TinyXML\tinyxml2.h"

enum class BodyType
{
	STATIC,
	KINEMATIC,
	DYNAMIC,
	SENSOR,
	DANGER
};

enum class Sides
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

class Level
{
	int level_width, level_height, tile_width, tile_height;
	bool strong_player_now;
	std::list<Object> unchangeable_objects;
	std::list<Object> changeable_objects;
	Storage storage;
	Player* player;
	StrongPlayer* strong_player;
	DexterousPlayer* dexterous_player;
	Object* bonus_UI[3];
	Bonus* activate_this_bonus;
	Bonus* active_bonus[3];
	b2World* level_world;
	MyContactListener* my_contact_listener_ptr;
	void loadMap(tinyxml2::XMLElement *map);
	void loadObjects(tinyxml2::XMLElement *map);
	void loadObject(tinyxml2::XMLElement *objectgroup, BodyType b_type);
	void parsePlatform(tinyxml2::XMLElement *object, tinyxml2::XMLElement * objectgroup, b2Body* body);
	void parseSensor(tinyxml2::XMLElement *object, b2Body* body, std::vector<Action> stages);
	void parseTimer(tinyxml2::XMLElement *object, std::vector<Action> stages);
	void parseBridge(tinyxml2::XMLElement *object, b2Body* body, b2BodyDef* body_def, Object* tmp_obj);
	void parseDangerObject(tinyxml2::XMLElement *object, b2Body* body, Object* tmp_obj, tinyxml2::XMLElement * objectgroup);
	b2Body* createBorderSensor(b2Body* body, Object* tmp_obj, Sides);
	std::vector<Action> sensorStagesParser(std::vector<std::string> stages);
	tinyxml2::XMLElement * findAmongSiblings(tinyxml2::XMLElement * element, std::string name);
	std::vector<std::string> stringDelimiter(std::string init_str);
	std::vector<std::pair<double, double>> buildTrajectory(tinyxml2::XMLElement * objectgroup, std::string trajectory_name, bool* is_rounded);
	void createBonusUI();
	void updateUI();
public:
	Level();
	~Level();
	bool loadLevel(std::string filename);
	std::list<Object>& getUnchangeableObjectList();
	std::list<Object>& getChangeableObjectList();
	std::vector<std::string>& getImagesList();
	Player* returnActivePlayer();
	void changeCurrentHero();
	void tryToSwitchLever();
	void pickUpBox();
	void throwBox(double x, double y);
	void update();
};
