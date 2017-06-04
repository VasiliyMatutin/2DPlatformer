#pragma once
#include "Player.h"

class Final : public ContactObject
{
private:
	Player* my_player;
	bool is_contact, is_strong;
	void contactEvent(b2Contact*, bool);
public:
	Final(b2Body* body, bool is_strong);
	bool isReach();
};
