#include "DynamicObj.h"
#include <iostream>

DynamicObj::DynamicObj(int _max_frame, int _level_width, int _level_height, double _current_frequency, b2Body* _body, Object* _object) :
	max_frame(_max_frame),
	level_width(_level_width),
	level_height(_level_height),
	current_frequency(_current_frequency),
	body (_body),
	object (_object),
	img_row(3),
	on_ground(0),
	is_animated(1),
	x_speed(0),
	delta_x_speed(0),
	fixed_speed(10)
{
	body->SetUserData(this);
}

void DynamicObj::moveLeft()
{
	delta_x_speed -= fixed_speed;
}

void DynamicObj::stopLeft()
{
	delta_x_speed += fixed_speed;
}

void DynamicObj::moveRight()
{
	delta_x_speed += fixed_speed;
}

void DynamicObj::stopRight()
{
	delta_x_speed -= fixed_speed;
}

void DynamicObj::contactEvent(b2Contact * contact, bool is_begin)
{
	b2Manifold* contact_information = contact->GetManifold();
	switch (is_begin)
	{
	case 0:
		if (contact_information->localNormal.y < 0)
		{
			on_ground = 0;
			{
				b2Vec2 tmp = body->GetLinearVelocity();
				if (tmp.x != 0)
				{
					body->SetLinearVelocity(b2Vec2(0, tmp.y));
					body->ApplyLinearImpulse(b2Vec2(x_speed / 4 * body->GetMass(), 0), b2Vec2(body->GetPosition().x, body->GetPosition().y), 1);
				}
				return;
			};
		}

		if (contact_information->localNormal.x != 0)
		{
			is_animated = 1;
			return;
		}

	case 1:
		if (contact_information->localNormal.y < 0)
		{
			on_ground = 1;
			body->SetLinearVelocity(b2Vec2(0, 0));
			return;
		}

		if (contact_information->localNormal.x > 0 || contact_information->localNormal.x < 0)
		{
			is_animated = 0;
			if (body->GetLinearVelocity().y<0) body->SetLinearVelocity(b2Vec2(0, 0));
			return;
		}
	}
}

void DynamicObj::jump()
{
	if (on_ground) body->ApplyLinearImpulse(b2Vec2(0, -10 * body->GetMass()), b2Vec2(body->GetPosition().x, body->GetPosition().y), 1);
}

void DynamicObj::update()
{
	b2Vec2 tmp = body->GetLinearVelocity();
	if (on_ground) x_speed = delta_x_speed;
	else x_speed = tmp.x;
	if (object->x + object->width / 2 >= level_width - 1 && x_speed > 0 || object->x - object->width / 2 <= 1 && x_speed < 0) x_speed = 0; //check of collisions with level boundaries
	body->SetLinearVelocity(b2Vec2(x_speed, tmp.y));
	tmp = body->GetPosition();
	object->x = tmp.x;
	object->y = tmp.y;
	if (on_ground && x_speed != 0 && is_animated)
	{
		current_frame += current_frequency;
		if (current_frame > max_frame) current_frame -= max_frame - 1;
	}
	else
		current_frame = 0.9;
	object->left = object->width*(int)current_frame;
	object->top = object->height*img_row;
	if (is_animated && on_ground)
	{
		if (x_speed > 0) img_row = 3;
		if (x_speed < 0) img_row = 1;
	}
}

