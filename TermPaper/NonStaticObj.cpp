#include "NonStaticObj.h"

NonStaticObj::NonStaticObj(b2Body* _body, Object* _object, ObjectType type) :
	body(_body),
	object(_object),
	my_type(type),
	is_valid(1) {}

void NonStaticObj::contactEvent(b2Contact *, bool)
{
}

ObjectType NonStaticObj::whoAmI()
{
	return my_type;
}

b2Body * NonStaticObj::getBody()
{
	return body;
}

Object * NonStaticObj::getObject()
{
	return object;
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

bool NonStaticObj::destroy()
{
	if (is_valid)
	{
		for (b2JointEdge* edge = body->GetJointList(); edge; edge = edge->next)
		{
			if (edge->joint->GetBodyB()->GetType() != b2BodyType::b2_dynamicBody || edge->joint->GetBodyB()->GetFixtureList()->IsSensor() == true)
			{
				continue;
			}
			body->GetWorld()->DestroyJoint(edge->joint);
			return false;
		}
		object->is_valid = 0;
		body->GetWorld()->DestroyBody(body);
		is_valid = false;
	}
	return true;
}
