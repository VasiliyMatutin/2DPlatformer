#include "Sensor.h"

void Sensor::contactEvent(b2Contact * contact, bool is_begin)
{
	non_run = 0;
	if (contact->GetFixtureA()->GetBody()->GetType() != b2BodyType::b2_staticBody)
	{
		if (is_begin == true)
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
					it->makeAction(stages[stage_iter]);
				}
				return;
			}
		}
		else
		{
			is_pressed--;
			if (is_keeping == true && is_pressed == 0)
			{
				for (auto it : observables)
				{
					it->makeAction(stages[stage_iter]);
				}
			}
		}
		if (stage_iter == stages.size() - 1)
		{
			stage_iter = -1;
		}
		stage_iter++;
	}
	else
	{
		non_run = 1;
	}
}

Sensor::Sensor(std::list<ManualSwitchObj*> _observables, bool _repeat_allowed, bool _is_keeping, b2Body * _body, std::vector<Action> _stages):
	observables(_observables),
	repeat_allowed(_repeat_allowed),
	is_keeping(_is_keeping),
	is_pressed(0),
	stages(_stages),
	stage_iter(0)
{
	_body->SetUserData(this);
	if (stages.empty())
	{
		stages.push_back(Action::DEFAULT);
	}
}

