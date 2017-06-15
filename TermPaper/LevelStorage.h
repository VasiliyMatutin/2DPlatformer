/*! \file */

/**
\brief Class-container which contains information about objects on the Level
\author Vasily
\version 1.0
\date June 2017
*/

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
	///list of pointers to Lever entity
	std::list<Lever*> lever_list;
	///list of pointers to Timer entity
	std::list<Timer*> timer_list;
	///list of all pointers to NonStaticObj entities
	std::list<NonStaticObj*> non_static_objects;
	///list of pointers to sensors which attached to players
	std::list<PlayerSensor*> players_sensors_list;
	///list containing pointers to objects that will be destroyed at the next level update iteration
	std::list<NonStaticObj*>* to_destroy_list;
	///list of all pointers to DangerObject entities
	std::list<DangerObject*> danger_list;
	///contains pointers to final sensor (for both players)
	Final* final_list[2];
	///list of all pointers to Bonus entities
	std::list<Bonus*> bonus_list;
	///internal map which help to parse information about observables objects and pin them to the observer
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