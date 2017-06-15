/*! \file */

#pragma once
#include "ContactObject.h"
#include "LevelBox.h"
#include <chrono>

///Type of the bonus
enum class BonusType
{
	JUMP,///< increase/decrease jump heigth
	RUN,///< increase/decrease speed
	HEALTH///< increase/decrease healt
};

class Player;

/**
\brief Some serum that have an impact to the hero
\author Vasily
\version 1.0
\date June 2017
*/
class Bonus : public ContactObject
{
private:
	///pointer to the box2d body assigned to this bonus
	b2Body* body;
	///pointer to the Object class assigned to this bonus
	Object* object;
	///pointer to the Player class to which bonus has been applied
	Player* iam_activate_this_player;
	///pointer to the pointer containing infofmation about current active hero
	Player** current_player;
	///duration of the impact
	double time_interval;
	///current time that has passed from the begin of the bonus application
	double time;
	///power of the impact
	double bonus_modificator;
	///bonuse type (see enum BonusType)
	BonusType bonus_type;
	///chrono service information
	std::chrono::seconds dts;
	///pointer to the variable containing information about level time
	std::chrono::duration<double>* duration;
	///chrono start of impact
	std::chrono::duration<double> start;
	///inherited from ContactObject class
	void contactEvent(b2Contact* contact, bool is_begin);
public:
	/*!
	\brief Defined constructor for this class
	\param modificator power of the impact
	\param time duration of the impact
	\param bonus_type bonuse type (see enum BonusType)
	\param _current_player pointer to the pointer containing infofmation about current active hero
	\param _body pointer to the box2d body assigned to this bonus
	\param _object pointer to the Object class assigned to this bonus
	\param duration pointer to the variable containing information about level time
	*/
	Bonus(double modificator, double time, BonusType bonus_type, Player** _current_player, b2Body* _body, Object* _object, std::chrono::duration<double>* duration);
	/*!
	\return pointer to the Object class assigned to this bonus or bonus-cell
	*/
	Object* getObject();
	/*!
	\brief Apllies the bonus effect

	Delete the image of bonus from the screen and move it to hero ui bonus-cell
	\param _object pointer to Object class which define ui bonus-cell
	*/
	bool activate(Object* _object);
	/*!
	\brief Terminates the action of the bonus effect

	Delete the image of bonus from the hero ui bonus-cell
	*/
	void deactivate();
	///update bonus state (remaining time of impact)
	void update();
};