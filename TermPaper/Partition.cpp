#include "Partition.h"

Partition::Partition(b2Body * _body, Object * _object, b2RevoluteJoint * _joint): NonStaticObj(_body, _object),
joint(_joint),
is_joint_exist(1)
{
	body->GetFixtureList()->SetDensity(10.0f);
	body->GetFixtureList()->SetFriction(0.3f);
	body->ResetMassData();
	body->SetFixedRotation(false);
	body->SetUserData(this);
}

bool Partition::destroy(b2World * lvl_world)
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

void Partition::update()
{
	NonStaticObj::update();
}
