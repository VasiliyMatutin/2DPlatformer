#pragma once
#include <map>
#include "Platform.h"
#include "VisibleSensor.h"
#include "Lever.h"
#include "Timer.h"
#include "DangerObject.h"
#include "RevoluteBridge.h"
#include "PlayerSensor.h"
#include "Bonus.h"
#include "Final.h"

class Storage
{
public:
	std::list<Lever*> lever_list;
	std::list<Timer*> timer_list;
	std::list<NonStaticObj*> non_static_objects;
	std::list<PlayerSensor*> players_sensors_list;
	std::list<NonStaticObj*>* to_destroy_list;
	std::list<DangerObject*> danger_list;
	Final* final_list[2];
	std::list<Bonus*> bonus_list;
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
		for (auto it : players_sensors_list)
		{
			delete it;
		}
		for (auto it : danger_list)
		{
			delete it;
		}
		for (auto it : bonus_list)
		{
			delete it;
		}
		for (auto it : final_list)
		{
			delete it;
		}
	}
};