#include "ManualPlatform.h"

ManualPlatform::ManualPlatform(int _level_width, int _level_height, b2Body * _body, Object * _object, std::vector<std::pair<double, double>> traj_coord, int _fixed_speed, bool _is_rounded, int _node_number) : Platform(_level_width, _level_height, _body, _object, traj_coord, _fixed_speed, _is_rounded, _node_number)
{
	Platform::is_active = false;
}

void ManualPlatform::update()
{
	if (ManualSwitchObj::is_active)
	{
		Platform::update();
		ManualSwitchObj::is_active = Platform::is_active;
	}
}

void ManualPlatform::makeAction(Action)
{
	if (ManualSwitchObj::is_active == false)
	{
		Platform::is_active = true;
		counter = backup_counter;
		point_iter -= incr;
		int back_counter_incr=counter_incr;
		counter_incr = 0;
		toNextPoint();
		counter_incr = back_counter_incr;
	}
	else
	{
		Platform::is_active = false;
		backup_counter = counter;
		body->SetLinearVelocity(b2Vec2(0, 0));
		counter = node_number + 1;
	}
	ManualSwitchObj::is_active = !ManualSwitchObj::is_active;
}

b2Body * ManualPlatform::getBody()
{
	return body;
}

Object * ManualPlatform::getObject()
{
	return object;
}
