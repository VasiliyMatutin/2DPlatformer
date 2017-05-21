#include "NonStaticObj.h"

NonStaticObj::NonStaticObj(b2Body* _body, Object* _object) :
	body(_body),
	object(_object),
	is_valid(1) {}

void NonStaticObj::contactEvent(b2Contact *, bool)
{
}

void NonStaticObj::update()
{
	if (!is_valid)
	{
		return;
	}
	b2Vec2 tmp = body->GetPosition();
	object->x = tmp.x * PIXEL_PER_METER;
	object->y = tmp.y * PIXEL_PER_METER;
	object->rotation = body->GetAngle();
}

bool NonStaticObj::destroy(b2World * lvl_world)
{
	if (is_valid)
	{
		object->is_valid = 0;
		lvl_world->DestroyBody(body);
		is_valid = false;
	}
	return true;
}
