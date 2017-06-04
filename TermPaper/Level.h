#pragma once
#include "Layer.h"
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

class Level : public Layer
{
	int level_width, level_height, tile_width, tile_height;
	bool strong_player_now;
	Storage storage;
	Player* player;
	StrongPlayer* strong_player;
	DexterousPlayer* dexterous_player;
	b2World* level_world;
	MyContactListener* my_contact_listener_ptr;
	std::list<Object> static_UI_objects;
	void loadMap(tinyxml2::XMLElement *map);
	void loadObjects(tinyxml2::XMLElement *map);
	void loadObject(tinyxml2::XMLElement *objectgroup, BodyType b_type);
	void parsePlatform(tinyxml2::XMLElement *object, tinyxml2::XMLElement * objectgroup, b2Body* body);
	void parseSensor(tinyxml2::XMLElement *object, b2Body* body, std::vector<Action> stages);
	void parseTimer(tinyxml2::XMLElement *object, std::vector<Action> stages);
	void parseBridge(tinyxml2::XMLElement *object, b2Body* body, b2BodyDef* body_def, Object* tmp_obj);
	void parseDangerObject(tinyxml2::XMLElement *object, b2Body* body, Object* tmp_obj, tinyxml2::XMLElement * objectgroup);
	b2Body* createBorderSensor(b2Body* body, Object* tmp_obj, Sides);
	void addUIToLevel();
	std::vector<Action> sensorStagesParser(std::vector<std::string> stages);
	tinyxml2::XMLElement * findAmongSiblings(tinyxml2::XMLElement * element, std::string name);
	std::vector<std::string> stringDelimiter(std::string init_str);
	std::vector<std::pair<double, double>> buildTrajectory(tinyxml2::XMLElement * objectgroup, std::string trajectory_name, bool* is_rounded);
	void changeCurrentHero();
	void tryToSwitchLever();
	void pickUpBox();
	void throwBox(double x, double y);
public:
	Level(std::string filename);
	~Level();
	bool loadLevel(std::string filename);
	void smthHappend(Events what_happened);
	bool isDoubleView();
	void getLayerSize(double* width, double* height);
	void getLayerCenter(double* x, double* y);
	void update();
};
