/*! \file */

#pragma once
#include "Layer.h"
#include "LevelStorage.h"
#include "StrongPlayer.h"
#include "DexterousPlayer.h"
#include "ContactListener.h"
#include "TinyXML\tinyxml2.h"

///Type of the *.tmx object group
enum class BodyType
{
	STATIC,///< simple static bodies
	KINEMATIC,///< force movable kinematic bodies
	DYNAMIC,///< common dynamic bodies
	SENSOR,///< see Sensor and similar
	DANGER///< see DangerObject
};

///Side of player sensor
enum class Sides
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

/**
\brief Contains all information about game level
\author Vasily
\version 1.0
\date June 2017
*/
class Level : public Layer
{
	///width of the level in pixels
	int level_width;
	///height of the level in pixels
	int level_height;
	///width of the one tile from tileset in pixels
	int tile_width;
	///height of the one tile from tileset in pixels
	int tile_height;
	///define type of the player that active now: 'true' - strong player; 'false' - dexterous player
	bool strong_player_now;
	///special prefixes that add to all images path (path to source file)
	std::string prefix;
	///Containt different level objects
	Storage storage;
	///Pointer to the current active player
	Player* player;
	///Pointer to the class of strong_player
	StrongPlayer* strong_player;
	///Pointer to the class of dexterous_player
	DexterousPlayer* dexterous_player;
	///box2d world which provide physics simulation for the level
	b2World* level_world;
	///Pointer to the ovveride standart box2d contact listener
	MyContactListener* my_contact_listener_ptr;
	///list with an objects of ui information of the level(health bar, bonuses cell etc.)
	std::list<Object> static_UI_objects;
	///chrono service information
	std::chrono::time_point<std::chrono::system_clock> prev_step;
	///time which that has passed since the begginning of the level(besides pauses)
	std::chrono::duration<double> level_time;
	/*!
	\brief internal function which parse tmx file and load information about level tiledmap
	\param map pointer to the xml object containing necessery information about map
	*/
	void loadMap(tinyxml2::XMLElement *map);
	/*!
	\brief internal function which parse tmx file and load information about object groups
	\param map pointer to the xml object containing necessery information about map
	*/
	void loadObjects(tinyxml2::XMLElement *map);
	/*!
	\brief internal function which parse tmx file and load information about object
	\param objectgroup pointer to the xml object containing necessery information about objects group
	\param b_type type of the *.tmx object group which object belong to
	*/
	void loadObject(tinyxml2::XMLElement *objectgroup, BodyType b_type);
	/*!
	\brief internal function which fill up information about platform & create it
	\param object pointer to the xml object containing necessery information about platform
	\param objectgroup pointer to the xml object containing necessery information about object group for this object
	\param body pointer to the box2d body assigned to this platform
	*/
	void parsePlatform(tinyxml2::XMLElement *object, tinyxml2::XMLElement * objectgroup, b2Body* body);
	/*!
	\brief internal function which fill up information about sensor & create it
	\param object pointer to the xml object containing necessery information about sensor
	\param body pointer to the box2d body assigned to this platform
	\param stages vector of stages(commands) through which observables objects of this sensor should pass throug
	*/
	void parseSensor(tinyxml2::XMLElement *object, b2Body* body, std::vector<Action> stages);
	/*!
	\brief internal function which fill up information about timer & create it
	\param object pointer to the xml object containing necessery information about timer
	\param stages vector of stages(commands) through which observables objects of this timer should pass throug
	*/
	void parseTimer(tinyxml2::XMLElement *object, std::vector<Action> stages);
	/*!
	\brief internal function which fill up information about bridge & create it
	\param object pointer to the xml object containing necessery information about bridge
	\param body pointer to the box2d body assigned to this bridge
	\param body_def pointer to the box2d system infroramation for this bridge body
	\param tmp_obj pointer to the Object class assigned to this bridge
	*/
	void parseBridge(tinyxml2::XMLElement *object, b2Body* body, b2BodyDef* body_def, Object* tmp_obj);
	/*!
	\brief internal function which fill up information about danger object & create it
	\param object pointer to the xml object containing necessery information about danger object
	\param body pointer to the box2d body assigned to this danger object
	\param tmp_obj pointer to the Object class assigned to this danger object
	\param objectgroup pointer to the xml object containing necessery information about object group for this object
	*/
	void parseDangerObject(tinyxml2::XMLElement *object, b2Body* body, Object* tmp_obj, tinyxml2::XMLElement * objectgroup);
	/*!
	\brief internal function which fill up information about special player sensor & create it
	\param body pointer to the box2d body to which sensor will be sticked
	\param tmp_obj pointer to the Object class assigned to this player sensort
	\param sides side of player to which sensor sticked
	\return pointer to the box2d body assigned to created player sensor
	*/
	b2Body* createBorderSensor(b2Body* body, Object* tmp_obj, Sides sides);
	///internal function which fill up information about level UI
	void addUIToLevel();
	/*!
	\brief internal function which transfer string information from from xml file to Action enum commands
	\param stages vector with commands in string format
	\return vector with commands in Action enum format
	*/
	std::vector<Action> sensorStagesParser(std::vector<std::string> stages);
	/*!
	\brief internal function which find an element in XML-file among similar
	\param element pointer to the first xml-element in group 
	\param name desired element name
	\return pointer to the xml-element with such name or nullptr
	*/
	tinyxml2::XMLElement * findAmongSiblings(tinyxml2::XMLElement * element, std::string name);
	/*!
	\brief subsidiary function which check existense of the element and throw exception if it isn't
	\tparam T - input variable
	\param smf_to_check template input variable
	\param error_msg string contains information which should be displayed if exception occured
	\return exactly the same variable as input 'smf_to_check'
	\throw string with message about non-existable object
	*/
	template<typename T>
	auto checkElementExistence(const T smf_to_check, std::string error_msg);
	/*!
	\brief subsidiary function which check existense of the file and throw exception if it isn't
	\param name name of the file for check
	\return exactly the same name as input 'name'
	\throw string with message about non-existable file
	*/
	std::string fileExistsTest(const std::string& name);
	/*!
	\brief subsidiary function which devides string using 'space' as delimiters
	\param init_str string prepared for separation
	\return vector of separating strings
	*/
	std::vector<std::string> stringDelimiter(std::string init_str);
	/*!
	\brief subsidiary function fill up vector with two-coordinates points of trajectory
	\param objectgroup pointer to the xml object containing necessery information about object group for this trajectory
	\param trajectory_name the name of the trajectory from the xml-file
	\param is_rounded pointer to the variable what defines the shape of trajectory 'true' - closed 'false' - torn
	\return vector with two-coordinates points of trajectory
	*/
	std::vector<std::pair<double, double>> buildTrajectory(tinyxml2::XMLElement * objectgroup, std::string trajectory_name, bool* is_rounded);
	///change active hero on the current level (from strong to dexterous for example)
	void changeCurrentHero();
	///send commant to hero to activate available lever
	void tryToSwitchLever();
	///send command to hero to pick up box(has an effect only for strong hero)
	void pickUpBox();
	/*!
	\brief send command to hero to throw box(has an effect only for strong hero)
	\param x coordinate of the mouse click
	\param y coordinate of the mouse click
	*/
	void throwBox(double x, double y);
	///subsidiary function which count time than has passed from the beggining of the level
	void countTime();
	/*!
	\brief subsidiary function which fill up information about, parsing *.tmx file
	\param filename path to the *.tmx file with information about this level
	\throw string with message about non-existable *.tmx file
	*/
	void loadLevel(std::string filename);
public:
	/*!
	\brief Defined constructor for this class
	\param prefix path to source files with images
	\param filename path to the *.tmx file with information about this level
	*/
	Level(std::string prefix, std::string filename);
	~Level();
	///inhereted from Layer class
	void smthHappend(Events what_happened);
	///inhereted from Layer class
	bool isDoubleView();
	///inhereted from Layer class
	void getLayerSize(double* width, double* height);
	///inhereted from Layer class
	void getLayerCenter(double* x, double* y);
	///inhereted from Layer class
	void update();
	///inhereted from Layer class
	void repause();
};

template<typename T>
inline auto Level::checkElementExistence(const T smf_to_check, std::string error_msg)
{
	if (smf_to_check == nullptr)
	{
		throw error_msg;
	}
	return smf_to_check;
}
