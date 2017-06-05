#pragma once
#include "ContactObject.h"
#include "Player.h"
#include <chrono>

class Bonus : public ContactObject
{
private:
	b2Body* body;
	Object* object;
	Player* iam_activate_this_player;
	Player** current_player;
	double time_interval, time, bonus_modificator;
	BonusType bonus_type;
	std::chrono::seconds dts;
	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::time_point<std::chrono::system_clock> end;
	std::chrono::duration<double> duration;
public:
	Bonus(double modificator, double time, BonusType bonus_type, Player** _current_player, b2Body* _body, Object* _object);
	void contactEvent(b2Contact*, bool);
	Object* getObject();
	bool activate(Object* _object);
	void deactivate();
	void update();
};