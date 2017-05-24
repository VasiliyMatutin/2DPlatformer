#include "RevoluteBridge.h"
#include "iostream"

RevoluteBridge::RevoluteBridge(b2Body * _body, Object * _object, b2RevoluteJoint* _bridge_joint, double _motor_speed): NonStaticObj(_body,_object, ObjectType::BRIDGE_PARTITION),
	motor_speed(_motor_speed),
	joint(_bridge_joint),
	is_joint_exist(1)
{
	body->SetUserData(this);
}

void RevoluteBridge::makeAction(Action action)
{
	if (!is_valid || !is_joint_exist)
	{
		return;
	}
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

bool RevoluteBridge::destroy()
{
	is_joint_exist = false;
	return NonStaticObj::destroy();
}

void RevoluteBridge::update()
{
	NonStaticObj::update();
}
