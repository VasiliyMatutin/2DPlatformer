#pragma once
#include "Sensor.h"
#include "Player.h"

class Lever : public ContactObject
{
private:
	b2Body * body;
	Object* object;
	Player** current_player;
	std::vector<Action> stages;
	std::list<ManualSwitchObj*> observables;
	int stage_iter;
	bool repeat_allowed; 
	void contactEvent(b2Contact*, bool);
public:
	Lever(std::list<ManualSwitchObj*> _observables, bool _repeat_allowed, b2Body * _body, Object* _object, Player** _current_player, std::vector<Action> _stages);
	void activate();
};