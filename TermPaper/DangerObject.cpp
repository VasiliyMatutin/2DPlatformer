#include "DangerObject.h"

void DangerObject::contactEvent(b2Contact * contact, bool is_begin)
{
	if (is_begin)
	{
		list_of_contact.push_back(static_cast<Player*>(contact->GetFixtureA()->GetBody()->GetUserData()));
		is_contact++;
	}
	else
	{
		for (auto it : list_of_contact)
		{
			if (it == contact->GetFixtureA()->GetBody()->GetUserData())
			{
				list_of_contact.remove(it);
				is_contact--;
				break;
			}
		}
	}
}

DangerObject::DangerObject(std::list<b2Body*> _boundaries, int _damage):
	is_contact(0),
	damage(_damage)
{
	for (auto it : _boundaries)
	{
		it->SetUserData(this);
	}
}

void DangerObject::update()
{
	if (is_contact)
	{
		for (auto it : list_of_contact)
		{
			it->decreaseHealth(damage);
		}
	}
}
