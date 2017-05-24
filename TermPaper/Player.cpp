#include "Player.h"
#include <iostream>

Player::Player(int _level_width, int _level_height, b2Body* _body, Object* _object, int _health) : NonStaticObj(_body, _object, ObjectType::PLAYER),
	level_width(_level_width),
	level_height(_level_height),
	health(_health),
	current_frequency(0.2),
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
	body->GetFixtureList()->SetFriction(0.3f);
	body->SetFixedRotation(true);
	body->SetUserData(this);
}

void Player::jump()
{
	if (on_ground) body->ApplyLinearImpulse(b2Vec2(0, -jump_strenght * body->GetMass()), b2Vec2(body->GetPosition().x, body->GetPosition().y), 1);
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
	//std::cout << "Kill me" << std::endl;
}

void Player::beginContactWithGround()
{
	on_ground = 1;
	body->ApplyLinearImpulseToCenter(b2Vec2(0, 0), 1);
}

void Player::endContactWithGround()
{
	on_ground = 0;
	b2Vec2 tmp = body->GetLinearVelocity();
	if (tmp.x != 0)
	{
		body->SetLinearVelocity(b2Vec2(0, tmp.y));
		body->ApplyLinearImpulseToCenter(b2Vec2(x_speed / 4 * body->GetMass(), 0), 1);
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
		is_animated = 1;
		x_speed = desired_vel;
		if (abs(vel.x) < 0.01)
		{
			is_animated = 0;
		}
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
		current_frame += abs(x_speed) / 20;
		if (current_frame > max_frame)
		{
			current_frame -= max_frame - 1;
		}
		if (x_speed > 0) img_row = right_row;
		if (x_speed < 0) img_row = left_row;
	}
	else
	{
		current_frame = 0.9;
	}
	object->left = object->width*(int)current_frame;
	object->top = object->height*img_row;
}
