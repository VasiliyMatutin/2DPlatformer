#pragma once
#include "ContactObject.h"
#include "Player.h"

class PlayerSensor : public ContactObject
{
private:
	int contact_count;
	Player* player;
public:
	PlayerSensor(Player* observable_player, b2Body* body);
	void contactEvent(b2Contact * contact, bool is_begin);
};
