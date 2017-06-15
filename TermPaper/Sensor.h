/*! \file */

/**
\brief Trigger that can activate observables ManualSwitchObj classes (dosen't display at the monitor)
\author Vasily
\version 1.0
\date June 2017
*/

#pragma once
#include <list>
#include <vector>
#include "ManualSwitchObj.h"
#include "LevelBox.h"
#include "ContactObject.h"

class Sensor : public ContactObject
{
protected:
	///list of observables objects
	std::list<ManualSwitchObj*> observables;
	///vector of stages(commands) through which observables objects should pass
	std::vector<Action> stages;
	///determines whether it is possible to send next command to the observables objects when they doesn't complete previous action: 'true' - possible; 'false' - impossible
	bool repeat_allowed;
	///determines will be next command send afther end of the contact(end of the hold button): 'true' - will be; 'false' - won't be
	bool is_keeping;
	///contain information about valid of the last contact: 'true' - sensor didn't respond; 'false' - sensor responded 
	bool non_run;
	///number of active contacts
	int is_pressed;
	///number of current stage from stages vector
	int stage_iter;
	///inherited from ContactObject class
	virtual void contactEvent(b2Contact* contact, bool is_begin);
public:
	/*!
	\brief Defined constructor for this class
	\param _observables list of observables objects
	\param _repeat_allowed determines whether it is possible to send next command to the observables objects when they doesn't complete previous action: 'true' - possible; 'false' - impossible
	\param _is_keeping determines will be next command send afther end of the contact(end of the hold button): 'true' - will be; 'false' - won't be
	\param _body pointer to the box2d body assigned to this sensor
	\param _stages vector of stages(commands) through which observables objects should pass
	*/
	Sensor(std::list<ManualSwitchObj*> _observables, bool _repeat_allowed, bool _is_keeping, b2Body * _body, std::vector<Action> _stages);
};
