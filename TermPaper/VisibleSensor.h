/*! \file */

/**
\brief Visible trigger that can activate observables ManualSwitchObj classes
\author Vasily
\version 1.0
\date June 2017
*/

#pragma once
#include "Sensor.h"
#include "Player.h"

class VisibleSensor : public Sensor
{
private:
	///pointer to the Object class assigned to this trigger
	Object* object;
	///inherited from ContactObject class
	void contactEvent(b2Contact* contact, bool is_begin);
public:
	/*!
	\brief Defined constructor for this class
	\param _observables list of observables objects
	\param _repeat_allowed determines whether it is possible to send next command to the observables objects when they doesn't complete previous action: 'true' - possible; 'false' - impossible
	\param _is_keeping determines will be next command send afther end of the contact(end of the hold button): 'true' - will be; 'false' - won't be
	\param _body pointer to the box2d body assigned to this sensor
	\param _object pointer to the Object class assigned to this sensor
	\param _stages vector of stages(commands) through which observables objects should pass
	*/
	VisibleSensor(std::list<ManualSwitchObj*> _observables, bool _repeat_allowed, bool _is_keeping, b2Body * _body, Object* _object, std::vector<Action> _stages);
};