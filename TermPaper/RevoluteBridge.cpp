#include "RevoluteBridge.h"
#include "iostream"

RevoluteBridge::RevoluteBridge(b2Body * _body, Object * _object, b2RevoluteJoint* _bridge_joint, double _motor_speed): Partition(_body,_object, _bridge_joint),
	motor_speed(_motor_speed)
{
	body->SetUserData(this);
}

void RevoluteBridge::makeAction(Action action)
{
	switch (action)
	{
	case Action::Up:
		joint->SetMotorSpeed(motor_speed);
		joint->EnableMotor(1);
		is_active = true;
		break;
	case Action::Down:
		joint->SetMotorSpeed(-motor_speed);
		joint->EnableMotor(1);
		is_active = true;
		break;
	case Action::Off:
		joint->EnableMotor(0);
		is_active = false;
		break;
	}
}

bool RevoluteBridge::destroy(b2World * lvl_world)
{
	if (is_joint_exist)
	{
		lvl_world->DestroyJoint(joint);
		is_joint_exist = false;
		return false;
	}
	else
	{
		if (is_valid)
		{
			object->is_valid = 0;
			lvl_world->DestroyBody(body);
			is_valid = false;
		}
		return true;
	}
	return false;
}

void RevoluteBridge::update()
{
	Partition::update();
}
