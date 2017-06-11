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
	std::chrono::duration<double>* duration;
	std::chrono::duration<double> start;
	void contactEvent(b2Contact*, bool);
public:
	DangerObject(std::list<b2Body*> _boundaries, double _damage, b2Body* body, std::chrono::duration<double>* _duration);
	void update();
};
