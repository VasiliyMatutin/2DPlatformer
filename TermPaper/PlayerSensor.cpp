#include "PlayerSensor.h"
#include <iostream>

PlayerSensor::PlayerSensor(Player * observable_player, b2Body* body) :
	player(observable_player),
	contact_count(0)
{
	b2Filter filter = body->GetFixtureList()->GetFilterData();
	filter.categoryBits = MASK_PLAYERS;
	filter.maskBits = MASK_PLAYER;
	body->GetFixtureList()->SetFilterData(filter);
	body->GetFixtureList()->SetFriction(23.3f);
	body->ResetMassData();
	body->SetUserData(this);
}

void PlayerSensor::contactEvent(b2Contact * contact, bool is_begin)
{
		if (is_begin)
		{
			if (contact_count == 0)
			{
				player->beginContactWithGround();
			}
			contact_count++;
		}
		else
		{
			contact_count--;
			if (contact_count == 0)
			{
				player->endContactWithGround();
			}
		}

}