#include "NonStaticObj.h"

NonStaticObj::NonStaticObj(b2Body* _body, Object* _object) :
	body(_body),
	object(_object) {}

void NonStaticObj::contactEvent(b2Contact *, bool)
{
}

void NonStaticObj::update()
{
	b2Vec2 tmp = body->GetPosition();
	object->x = tmp.x * PIXEL_PER_METER;
	object->y = tmp.y * PIXEL_PER_METER;
	object->rotation = body->GetAngle();
}

bool NonStaticObj::destroy(b2World * lvl_world)
{
	return false;
}
