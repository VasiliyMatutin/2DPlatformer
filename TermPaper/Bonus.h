#pragma once
#include "ContactObject.h"
#include "LevelBox.h"
#include <chrono>

///Type of the bonus
enum class BonusType
{
	JUMP,///< increase/decrease jump heigth
	RUN,///< increase/decrease speed
	HEALTH///< increase/decrease healt
};

class Player;

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
	std::chrono::duration<double>* duration;
	std::chrono::duration<double> start;
public:
	Bonus(double modificator, double time, BonusType bonus_type, Player** _current_player, b2Body* _body, Object* _object, std::chrono::duration<double>* duration);
	void contactEvent(b2Contact*, bool);
	Object* getObject();
	bool activate(Object* _object);
	void deactivate();
	void update();
};