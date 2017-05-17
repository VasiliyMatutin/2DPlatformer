#pragma once
#include "ContactObject.h"
#include "ManualSwitchObj.h"
#include "Partition.h"

class RevoluteBridge : public Partition, public ManualSwitchObj
{
private:
	double motor_speed;
public:
	RevoluteBridge(b2Body* _body, Object* _object, b2RevoluteJoint* _bridge_joint, double _motor_speed);
	void makeAction(Action);
	bool destroy(b2World* lvl_world);
	void update();
};
