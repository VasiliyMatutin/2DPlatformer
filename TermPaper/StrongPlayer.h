#pragma once
#include "Player.h"

class StrongPlayer : public Player
{
private:
	b2Joint* joint;
	b2Body* box;
	double box_coef;
	bool is_joint_set;
public:
	StrongPlayer(int _level_width, int _level_height, b2Body * _body, Object * _object, int _health);
	void tryToPickupBox();
	void throwBox(double x, double y);
	void update();
};
