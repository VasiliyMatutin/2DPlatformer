#pragma once
#include "ContactObject.h"
#include "Player.h"

class PlayerSensor : public ContactObject
{
private:
	int contact_count;
	Player* player;
	Sides side;
public:
	PlayerSensor(Player* observable_player, b2Body* body, Sides _side);
	void contactEvent(b2Contact * contact, bool is_begin);
};
