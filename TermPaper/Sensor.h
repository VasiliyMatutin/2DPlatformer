#pragma once
#include <list>
#include "ManualSwitchObj.h"
#include "LevelBox.h"
#include "ContactObject.h"

class Sensor : public ContactObject
{
protected:
	std::list<ManualSwitchObj*> observables;
	bool repeat_allowed, is_keeping;
	int is_pressed;
	virtual void contactEvent(b2Contact*, bool);
public:
	Sensor(std::list<ManualSwitchObj*> _observables, bool _repeat_allowed, bool is_keeping, b2Body * _body);
};
