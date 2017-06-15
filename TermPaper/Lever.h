/*! \file */

/**
\brief Special sensor that can be activated only by hero
\author Vasily
\version 1.0
\date June 2017
*/

#pragma once
#include "Sensor.h"
#include "Player.h"

class Lever : public ContactObject
{
private:
	///pointer to the box2d body assigned to this lever
	b2Body * body;
	///pointer to the Object class assigned to this lever
	Object* object;
	///pointer to the pointer containing infofmation about current active hero
	Player** current_player;
	///vector of stages(commands) through which observables objects should pass
	std::vector<Action> stages;
	///list of observables objects
	std::list<ManualSwitchObj*> observables;
	///number current stage from stages vector
	int stage_iter;
	///determines whether it is possible to send next command to the observables objects when they doesn't complete previous action: 'true' - possible; 'false' - impossible
	bool repeat_allowed; 
	///inherited from ContactObject class
	void contactEvent(b2Contact* contact, bool is_begin);
public:
	/*!
	\brief Defined constructor for this class
	\param _observables list of observables objects
	\param _repeat_allowed determines whether it is possible to send next command to the observables objects when they doesn't complete previous action: 'true' - possible; 'false' - impossible
	\param _body pointer to the box2d body assigned to this entity
	\param _object pointer to the Object class assigned to this entity
	\param _current_player pointer to the pointer containing infofmation about current active hero
	\param _stages vector of stages(commands) through which observables objects should pass
	*/
	Lever(std::list<ManualSwitchObj*> _observables, bool _repeat_allowed, b2Body * _body, Object* _object, Player** _current_player, std::vector<Action> _stages);
	///causes the lever try to send next command to observables objects
	void activate();
};