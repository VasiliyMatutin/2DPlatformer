#include "Player.h"
#include <iostream>

Player::Player(int _max_frame, int _level_width, int _level_height, double _current_frequency, b2Body* _body, Object* _object, int _fixed_speed, int _health) : NonStaticObj(_body, _object),
	max_frame(_max_frame),
	fixed_speed(_fixed_speed),
	current_frequency(_current_frequency),
	level_width(_level_width),
	level_height(_level_height),
	health(_health),
	x_speed(0),
	desired_vel(0),
	img_row(3),
	on_ground(0),
	is_animated(1)
{
	b2Filter filter = body->GetFixtureList()->GetFilterData();
	filter.categoryBits = PLAYER;
	filter.maskBits = MASK_PLAYER;
	body->GetFixtureList()->SetFilterData(filter);
	body->GetFixtureList()->SetDensity(1.0f);
	body->GetFixtureList()->SetFriction(0.3f);
	body->ResetMassData();
	body->SetFixedRotation(true);
	body->SetUserData(this);
}

void Player::jump()
{
	if (on_ground) body->ApplyLinearImpulse(b2Vec2(0, -5.5 * body->GetMass()), b2Vec2(body->GetPosition().x, body->GetPosition().y), 1);
}

void Player::moveLeft()
{
	desired_vel -= fixed_speed;
}

void Player::moveRight()
{
	desired_vel += fixed_speed;
}

void Player::stopRight()
{
	desired_vel -= fixed_speed;
}

void Player::stopLeft()
{
	desired_vel += fixed_speed;
}

void Player::decreaseHealth(int _healt_loss)
{
	std::cout << "Kill me" << std::endl;
}

void Player::beginContact(Sides side)
{
	switch (side)
	{
	case Sides::LEFT:
	case Sides::RIGHT:
		is_animated = 0;
		if (body->GetLinearVelocity().y < 0)
		{
			body->SetLinearVelocity(b2Vec2(0, 0));
		}
		return;
	case Sides::DOWN:
		on_ground = 1;
		body->ApplyLinearImpulseToCenter(b2Vec2(0, 0), 1);
		return;
	}
}

void Player::endContact(Sides side)
{
	switch (side)
	{
	case Sides::LEFT:
	case Sides::RIGHT:
	{
		is_animated = 1;
		return;
	}
	case Sides::DOWN:
	{
		on_ground = 0;
		b2Vec2 tmp = body->GetLinearVelocity();
		if (tmp.x != 0)
		{
			body->SetLinearVelocity(b2Vec2(0, tmp.y));
			body->ApplyLinearImpulseToCenter(b2Vec2(x_speed / 4 * body->GetMass(), 0), 1);
		}
		return;
	}
	}
}

void Player::returnCoordinates(double* x, double* y)
{
	*x = object->x;
	*y = object->y;
}

void Player::update()
{
	b2Vec2 vel = body->GetLinearVelocity();
	if (on_ground)
	{
		x_speed = desired_vel;
	}
	else
	{
		x_speed = vel.x;
	}
	if (object->x + object->width / 2 >= level_width - 1 && x_speed > 0 || object->x - object->width / 2 <= 1 && x_speed < 0) //check of collisions with level boundaries
	{
		x_speed = 0;
	}
	float velChange = x_speed - vel.x;
	float impulse = body->GetMass() * velChange;
	body->ApplyLinearImpulseToCenter(b2Vec2(impulse, 0), 1);

	NonStaticObj::update();
	if (on_ground && x_speed != 0 && is_animated)
	{
		current_frame += current_frequency;
		if (current_frame > max_frame)
		{
			current_frame -= max_frame - 1;
		}
	}
	else
		current_frame = 0.1;
	object->left = object->width*(int)current_frame;
	object->top = object->height*img_row;
	if (is_animated && on_ground)
	{
		if (x_speed > 0) img_row = 3;
		if (x_speed < 0) img_row = 1;
	}
}
