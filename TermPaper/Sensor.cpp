#include "Sensor.h"

void Sensor::contactEvent(b2Contact * contact, bool is_begin)
{
	if (contact->GetFixtureA()->GetBody()->GetUserData() != nullptr)
	{
		if (is_begin == 1)
		{
			is_pressed++;
			if (is_pressed == 1)
			{
				if (!repeat_allowed)
				{
					for (auto it : observables)
					{
						if (it->isActive() == true)
						{
							return;
						}
					}
				}
				for (auto it : observables)
				{
					it->makeAction();
				}
				return;
			}
		}

		if (is_begin == false)
		{
			is_pressed--;
			if (is_keeping == true)
			{
				for (auto it : observables)
				{
					it->makeAction();
				}
			}
		}
	}
	else
	{
		throw - 1;
	}
}

Sensor::Sensor(std::list<ManualSwitchObj*> _observables, bool _repeat_allowed, bool is_keeping, b2Body * _body):
	observables(_observables),
	repeat_allowed(_repeat_allowed),
	is_keeping(is_keeping),
	is_pressed(0)
{
	_body->SetUserData(this);
}
