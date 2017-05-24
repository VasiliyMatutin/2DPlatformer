#pragma once
#include "ContactObject.h"
#include "ManualSwitchObj.h"
#include "NonStaticObj.h"

class RevoluteBridge : public NonStaticObj, public ManualSwitchObj
{
private:
	double motor_speed;
	b2RevoluteJoint* joint;
	bool is_joint_exist;
public:
	RevoluteBridge(b2Body* _body, Object* _object, b2RevoluteJoint* _bridge_joint, double _motor_speed);
	void makeAction(Action);
	bool destroy();
	void update();
};
