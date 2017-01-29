#include "DynamicObj.h"

DynamicObj::DynamicObj(int _max_frame, double _current_frequency, b2Body* _body, Object* _object) :
	max_frame(_max_frame),
	current_frequency(_current_frequency),
	body (_body),
	object (_object),
	is_move(0),
	img_row(3)
{
}

void DynamicObj::moveLeft()
{
	img_row = 1;
	b2Vec2 tmp = body->GetLinearVelocity();
	body->SetLinearVelocity(b2Vec2(-10, tmp.y));
	is_move = 1;
}

void DynamicObj::moveRight()
{
	img_row = 3;
	b2Vec2 tmp = body->GetLinearVelocity();
	body->SetLinearVelocity(b2Vec2(10, tmp.y));
	is_move = 1;
}

void DynamicObj::stop()
{
	b2Vec2 tmp = body->GetLinearVelocity();
	body->SetLinearVelocity(b2Vec2(0, tmp.y));
	current_frame = 0.9;
	is_move = 0;
}

void DynamicObj::update()
{
	b2Vec2 tmp = body->GetPosition();
	object->x = tmp.x;
	object->y = tmp.y;
	if (is_move)
	{
		current_frame += current_frequency;
		if (current_frame > max_frame) current_frame -= max_frame - 1;
	}
	object->left = object->width*(int)current_frame;
	object->top = object->height*img_row;
}

