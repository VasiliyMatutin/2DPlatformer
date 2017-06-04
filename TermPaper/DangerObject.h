#pragma once
#include <vector>
#include <list>
#include <chrono>
#include "Player.h"

class DangerObject: public ContactObject
{
private:
	std::vector<Player*> list_of_contact;
	int is_contact;
	double damage, time_interval, time;
	std::chrono::milliseconds dts;
	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::time_point<std::chrono::system_clock> end;
	std::chrono::duration<double> duration;
	void contactEvent(b2Contact*, bool);
public:
	DangerObject(std::list<b2Body*> _boundaries, double _damage, b2Body* body);
	void update();
};
