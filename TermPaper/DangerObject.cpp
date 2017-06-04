#include "DangerObject.h"

void DangerObject::contactEvent(b2Contact * contact, bool is_begin)
{
	if (is_begin)
	{
		list_of_contact.push_back(static_cast<Player*>(contact->GetFixtureA()->GetBody()->GetUserData()));
		if (!is_contact)
		{
			start = std::chrono::system_clock::now();
		}
		is_contact++;
	}
	else
	{
		for (int i = 0; i < list_of_contact.size(); ++i)
		{
			if (list_of_contact[i] == contact->GetFixtureA()->GetBody()->GetUserData())
			{
				list_of_contact.erase(list_of_contact.begin()+i);
				is_contact--;
				break;
			}
		}
	}
}

DangerObject::DangerObject(std::list<b2Body*> _boundaries, double _damage, b2Body* body):
	is_contact(0),
	damage(_damage)
{
	b2Filter filter;
	filter.categoryBits = DANGERS;
	filter.maskBits = MASK_DANGERS;
	body->GetFixtureList()->SetFilterData(filter);
	for (auto it : _boundaries)
	{
		it->GetFixtureList()->SetFilterData(filter);
		it->SetUserData(this);
	}
	time_interval = 100;
}

void DangerObject::update()
{
	if (is_contact)
	{
		end = std::chrono::system_clock::now();
		duration = end - start;
		dts = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
		time = dts.count();
		if (time > time_interval)
		{
			for (int i=0; i < list_of_contact.size(); ++i)
			{
				list_of_contact[i]->activate_bonus(-damage, BonusType::HEALTH);
			}
			start = std::chrono::system_clock::now();
		}
	}
}
