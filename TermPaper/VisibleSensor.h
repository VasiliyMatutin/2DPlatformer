#pragma once
#include "Sensor.h"
#include "Player.h"

class VisibleSensor : public Sensor
{
private:
	Object* object;
	void contactEvent(b2Contact*, bool);
public:
	VisibleSensor(std::list<ManualSwitchObj*> _observables, bool _repeat_allowed, bool is_keeping, b2Body * _body, Object* _object, std::vector<Action> _stages);
};