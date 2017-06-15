/*! \file */

/**
\brief Danger entity that can be assigned to the platform
\author Vasily
\version 1.0
\date June 2017
*/

#pragma once
#include <vector>
#include <list>
#include <chrono>
#include "Player.h"

class DangerObject: public ContactObject
{
private:
	///list of players which have contact with this danger object
	std::vector<Player*> list_of_contact;
	///power of the damage (health_loss)
	double damage;
	///duration of the time intervals with which the damage will be applied
	double time_interval;
	///current time that has passed from the begin of the bonus application
	double time;
	///chrono service information
	std::chrono::milliseconds dts;
	///pointer to the variable containing information about level time
	std::chrono::duration<double>* duration;
	///chrono start of impact
	std::chrono::duration<double> start;
	///inherited from ContactObject class
	void contactEvent(b2Contact* contact, bool is_begin);
public:
	/*!
	\brief Defined constructor for this class
	\param _boundaries list of pointer to the sensors which stick to this danger object
	\param _damage power of the damage (health_loss)
	\param body pointer to the box2d body assigned to this danger object
	\param _duration pointer to the variable containing information about level time
	*/
	DangerObject(std::list<b2Body*> _boundaries, double _damage, b2Body* body, std::chrono::duration<double>* _duration);
	///update bonus state (should it to make damage or not)
	void update();
};
