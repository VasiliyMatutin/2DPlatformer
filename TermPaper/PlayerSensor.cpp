#include "PlayerSensor.h"
#include <iostream>

PlayerSensor::PlayerSensor(Player * observable_player, b2Body* body, Sides _side) :
	side(_side),
	player(observable_player),
	contact_count(0)
{
	b2Filter filter = body->GetFixtureList()->GetFilterData();
	filter.categoryBits = PLAYER;
	filter.maskBits = MASK_PLAYER;
	body->GetFixtureList()->SetFilterData(filter);
	body->SetUserData(this);
}

void PlayerSensor::contactEvent(b2Contact * contact, bool is_begin)
{
	if (is_begin)
	{
		if (contact_count == 0)
		{
			player->beginContact(side);
		}
		std::cout << "++" << std::endl;
		contact_count++;
	}
	else
	{
		std::cout << "--" << std::endl;
		contact_count--;
		if (contact_count == 0)
		{
			player->endContact(side);
		}
	}
}