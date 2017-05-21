#pragma once
#include <list>
#include "Player.h"

class DangerObject: public ContactObject
{
protected:
	std::list<Player*> list_of_contact;
	int is_contact, damage;
	void contactEvent(b2Contact*, bool);
public:
	DangerObject(std::list<b2Body*> _boundaries, int _damage, b2Body* body);
	void update();
};
