#include "Player.h"

Player::Player(int _max_frame, int _level_width, int _level_height, double _current_frequency, b2Body* _body, Object* _object, int _fixed_speed) : NonStaticObj(_body, _object),
	max_frame(_max_frame),
	fixed_speed(_fixed_speed),
	current_frequency(_current_frequency),
	level_width(_level_width),
	level_height(_level_height),
	x_speed(0),
	delta_x_speed(0),
	img_row(3),
	on_ground(0),
	is_animated(1)
{
	b2Filter filter = body->GetFixtureList()->GetFilterData();
	filter.categoryBits = PLAYER;
	body->GetFixtureList()->SetFilterData(filter);
	body->GetFixtureList()->SetDensity(1.0f);
	body->GetFixtureList()->SetFriction(0.3f);
	body->ResetMassData();
	body->SetFixedRotation(true);
	body->SetUserData(this);
}

void Player::jump()
{
	if (on_ground) body->ApplyLinearImpulse(b2Vec2(0, -5 * body->GetMass()), b2Vec2(body->GetPosition().x, body->GetPosition().y), 1);
}

void Player::moveLeft()
{
	delta_x_speed -= fixed_speed;
}

void Player::moveRight()
{
	delta_x_speed += fixed_speed;
}

void Player::stopRight()
{
	delta_x_speed -= fixed_speed;
}

void Player::stopLeft()
{
	delta_x_speed += fixed_speed;
}

void Player::contactEvent(b2Contact * contact, bool is_begin)
{
	b2Manifold* contact_information = contact->GetManifold();
	b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);
	if (is_begin == 0)
	{
		if (contact_information->localNormal.y != 0)
		{
			if (contact->GetFixtureA()->GetBody()->GetUserData() == nullptr)
			{
				on_ground = 0;
			}
				b2Vec2 tmp = body->GetLinearVelocity();
				if (tmp.x != 0)
				{
					body->SetLinearVelocity(b2Vec2(0, tmp.y));
					body->ApplyLinearImpulse(b2Vec2(x_speed / 4 * body->GetMass(), 0), b2Vec2(body->GetPosition().x, body->GetPosition().y), 1);
				}
				return;
		}

		if (contact_information->localNormal.x != 0)
		{
			is_animated = 1;
			return;
		}
	}
	else
	{
		if (contact_information->localNormal.y != 0 && worldManifold.points[0].y - object->y / PIXEL_PER_METER > 0)
		{
			on_ground=1;
			body->ApplyLinearImpulse(b2Vec2(0, 0), b2Vec2(body->GetPosition().x, body->GetPosition().y), 1);
			return;
		}

		if (contact_information->localNormal.x > 0 || contact_information->localNormal.x < 0)
		{
			is_animated = 0;
			if (body->GetLinearVelocity().y < 0)
			{
				body->SetLinearVelocity(b2Vec2(0, 0));
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
	b2Vec2 tmp = body->GetLinearVelocity();
	if (on_ground)
	{
		x_speed = delta_x_speed;
	}
	else x_speed = tmp.x;
	if (object->x + object->width / 2 >= level_width - 1 && x_speed > 0 || object->x - object->width / 2 <= 1 && x_speed < 0) x_speed = 0; //check of collisions with level boundaries
	body->SetLinearVelocity(b2Vec2(x_speed, tmp.y));
	NonStaticObj::update();
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
