#pragma once
#include <map>
#include "Platform.h"
#include "VisibleSensor.h"
#include "Lever.h"
#include "Timer.h"
#include "RevoluteBridge.h"

class Storage
{
public:
	std::list<Lever*> lever_list;
	std::list<Timer*> timer_list;
	std::list<NonStaticObj*> non_static_objects;
	std::list<NonStaticObj*>* to_destroy_list;
	std::map<std::string, ManualSwitchObj*> future_observables;
	~Storage()
	{
		for (auto it : non_static_objects)
		{
			if (it)
			{
				delete it;
			}
		}
		for (auto it : lever_list)
		{
			delete it;
		}
		for (auto it : timer_list)
		{
			delete it;
		}
	}
};