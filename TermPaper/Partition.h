#pragma once
#include "ContactObject.h"
#include "LevelBox.h"
#include "NonStaticObj.h"

class Partition : public NonStaticObj
{
protected:
	b2RevoluteJoint* joint;
	bool is_joint_exist;
public:
	Partition(b2Body* _body, Object* _object, b2RevoluteJoint* _joint);
	bool destroy(b2World* lvl_world);
	void update();
};
