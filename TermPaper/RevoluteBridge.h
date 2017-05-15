#pragma once
#include "ContactObject.h"
#include "LevelBox.h"
#include "ManualSwitchObj.h"
//#include "NonStaticObj.h"

class RevoluteBridge : public ManualSwitchObj
{
private:
	b2Body* body;
	Object* object;
	b2RevoluteJoint* bridge_joint;
	double motor_speed;
public:
	RevoluteBridge(b2Body* _body, Object* _object, b2RevoluteJoint* _bridge_joint, double _motor_speed);
	void update();
	void makeAction(Action);
};
