#pragma once
#include <list>
#include <vector>
#include "ManualSwitchObj.h"
#include "LevelBox.h"
#include "ContactObject.h"

class Sensor : public ContactObject
{
protected:
	std::list<ManualSwitchObj*> observables;
	std::vector<Action> stages;
	bool repeat_allowed, is_keeping, non_run;
	int is_pressed,stage_iter;
	virtual void contactEvent(b2Contact*, bool);
public:
	Sensor(std::list<ManualSwitchObj*> _observables, bool _repeat_allowed, bool _is_keeping, b2Body * _body, std::vector<Action> _stages);
};
