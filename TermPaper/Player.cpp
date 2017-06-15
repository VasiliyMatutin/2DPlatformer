#include "Player.h"
#include "Bonus.h"

Player::Player(int _level_width, int _level_height, b2Body* _body, Object* _object, int _health, ReturnEvents* _re) : NonStaticObj(_body, _object, ObjectType::PLAYER),
	level_width(_level_width),
	level_height(_level_height),
	max_health(_health),
	re(_re),
	current_frequency(0.2),
	x_speed(0),
	desired_vel(0),
	img_row(3),
	on_ground(1),
	is_animated(1),
	is_stop(0)
{
	health = max_health;
	body->GetFixtureList()->SetFriction(0.3f);
	body->ResetMassData();
	body->SetFixedRotation(true);
	body->SetUserData(this);
}

void Player::activate_bonus(double modificator, BonusType bonus_type)
{
	switch (bonus_type)
	{
	case BonusType::JUMP:
	{
		jump_strenght *= modificator;
		break;
	}
	case BonusType::RUN:
	{
		desired_vel *= modificator;
		fixed_speed *= modificator;
		break;
	}
	case BonusType::HEALTH:
	{
		health += modificator;
		if (health > max_health)
		{
			health = max_health;
		}
		else if (health <= 0)
		{
			health = 0;
			destroy();
			break;
		}
	}
	}
}

void Player::deactivate_bonus(double modificator, BonusType bonus_type)
{
	switch (bonus_type)
	{
	case BonusType::JUMP:
	{
		jump_strenght /= modificator;
		break;
	}
	case BonusType::RUN:
	{
		desired_vel /= modificator;
		fixed_speed /= modificator;
		break;
	}
	}
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
	is_stop = true;
}

void Player::stopLeft()
{
	desired_vel += fixed_speed;
	is_stop = true;
}

void Player::justStop()
{
	if (on_ground)
	{
		desired_vel = 0;
	}
}

double Player::getVel()
{
	return desired_vel;
}

void Player::setVel(double des_vel)
{
	if (des_vel == 0)
	{
		return;
	}
	if (des_vel*-1 > 0)
	{
		moveLeft();
	}
	else
	{
		moveRight();
	}
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

Bonus ** Player::getActivationBonus()
{
	return &activate_this_bonus;
}

void Player::returnCoordinates(double* x, double* y)
{
	*x = object->x;
	*y = object->y;
}

PlayerUI * Player::returnUI()
{
	return &playerUI;
}

bool Player::destroy()
{
	if (NonStaticObj::destroy())
	{
		object->is_valid = true;
		*re = ReturnEvents::GAMEOVER;
		return true;
	}
	else
	{
		return false;
	}
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
	if (object->y + object->height / 2 >= level_height - 1 && vel.y > 0 || object->y - object->height / 2 <= 1 && vel.y < 0) //check of collisions with level boundaries
	{
		health = 0;
		destroy();
		return;
	}
	if (desired_vel!=0)
	{
		float velChange = x_speed - vel.x;
		float impulse = body->GetMass() * velChange;
		body->ApplyLinearImpulseToCenter(b2Vec2(impulse, 0), 1);
	}
	else
	{
		if (is_stop)
		{
			float velChange = x_speed - vel.x;
			float impulse = body->GetMass() * velChange;
			body->ApplyLinearImpulseToCenter(b2Vec2(impulse, 0), 1);
			is_stop = false;
		}
	}

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
	updateUI();
}

void Player::updateUI()
{
	for (int i = 0; i < 3; ++i)
	{
		if (active_bonus[i])
		{
			if (playerUI.getActiveBonusesPtr(i)->is_valid == 0)
			{
				active_bonus[i] = nullptr;
			}
			else
			{
				active_bonus[i]->update();
			}
		}
	}
	if (activate_this_bonus)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (playerUI.getActiveBonusesPtr(i)->is_valid == 0)
			{
				activate_this_bonus->activate(playerUI.getActiveBonusesPtr(i));
				active_bonus[i] = activate_this_bonus;
				activate_this_bonus = nullptr;
				return;
			}
		}
		active_bonus[0]->deactivate();
		activate_this_bonus->activate(playerUI.getActiveBonusesPtr(0));
		active_bonus[0] = activate_this_bonus;
		activate_this_bonus = nullptr;
	}
	if (health < 0)
	{
		health = 0;
	}
	playerUI.getHealthPtr()->width = 99 * health / max_health;
	return;
}
