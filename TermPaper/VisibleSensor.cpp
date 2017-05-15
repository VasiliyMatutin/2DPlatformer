#include "VisibleSensor.h"

void VisibleSensor::contactEvent(b2Contact * contact, bool is_begin)
{
	try
	{
		Sensor::contactEvent(contact, is_begin);
	}
	catch (int ex)
	{
		return;
	}
	if (is_begin == 1)
	{
		object->left = 0;
		object->top = 16;
	}
	else
	{
		if (is_pressed == 0)
		{
			object->left = 0;
			object->top = 0;
		}
	}
}

VisibleSensor::VisibleSensor(std::list<ManualSwitchObj*> _observables, bool _repeat_allowed, bool is_keeping, b2Body * _body, Object * _object, std::vector<Action> _stages) : Sensor(_observables, _repeat_allowed, is_keeping, _body, _stages),
	object(_object)
{
	_body->SetUserData(this);
}
