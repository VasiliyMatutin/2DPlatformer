#include "DynamicObj.h"

void DynamicObj::contactChecker()
{
	on_ground = 0;
	for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next)
	{
		int numPoints = edge->contact->GetManifold()->pointCount;
		b2WorldManifold worldManifold;
		edge->contact->GetWorldManifold(&worldManifold);
		if (!on_ground && worldManifold.normal.y < 0)
		{
			on_ground = 1;
			continue;
		}
		if ((worldManifold.normal.x > 0 && x_speed < 0) || (worldManifold.normal.x < 0 && x_speed > 0)) stop();
	}
}

DynamicObj::DynamicObj(int _max_frame, int _level_width, int _level_height, double _current_frequency, b2Body* _body, Object* _object) :
	max_frame(_max_frame),
	level_width(_level_width),
	level_height(_level_height),
	current_frequency(_current_frequency),
	body (_body),
	object (_object),
	is_move(0),
	img_row(3),
	x_speed(0),
	on_ground(0)
{
}

void DynamicObj::moveLeft()
{
	img_row = 1;
	x_speed = -10;
	is_move = 1;
}

void DynamicObj::moveRight()
{
	img_row = 3;
	x_speed = 10;
	is_move = 1;
}

void DynamicObj::jump()
{
	if (on_ground) body->ApplyLinearImpulse(b2Vec2(0, -10 * body->GetMass()), b2Vec2(body->GetPosition().x, body->GetPosition().y), 1);
}

void DynamicObj::stop()
{
	x_speed = 0;
	current_frame = 0.9;
	is_move = 0;
}

void DynamicObj::update()
{
	contactChecker();
	if (object->x + object->width / 2 >= level_width - 1 && x_speed > 0 || object->x - object->width / 2 <= 1 && x_speed < 0) stop();
	b2Vec2 tmp = body->GetLinearVelocity();
	body->SetLinearVelocity(b2Vec2(x_speed, tmp.y));
	tmp = body->GetPosition();
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

