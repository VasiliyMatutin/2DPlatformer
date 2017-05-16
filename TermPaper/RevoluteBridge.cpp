#include "RevoluteBridge.h"

RevoluteBridge::RevoluteBridge(b2Body * _body, Object * _object, b2RevoluteJoint* _bridge_joint, double _motor_speed): NonStaticObj(_body,_object),
	bridge_joint(_bridge_joint),
	motor_speed(_motor_speed)
{
	body->GetFixtureList()->SetDensity(10.0f);
	body->GetFixtureList()->SetFriction(0.3f);
	body->ResetMassData();
	body->SetFixedRotation(false);
}

void RevoluteBridge::makeAction(Action action)
{
	switch (action)
	{
	case Action::Up:
		bridge_joint->SetMotorSpeed(motor_speed);
		bridge_joint->EnableMotor(1);
		is_active = true;
		break;
	case Action::Down:
		bridge_joint->SetMotorSpeed(-motor_speed);
		bridge_joint->EnableMotor(1);
		is_active = true;
		break;
	case Action::Off:
		bridge_joint->EnableMotor(0);
		is_active = false;
		break;
	}
}
