#pragma once
#include "NonStaticObj.h"
#include "PlayerUI.h"
#include "Events.h"

enum class BonusType
{
	JUMP,
	RUN,
	HEALTH
};

class Bonus;

class Player : public NonStaticObj
{
protected:
	int img_row, left_row, right_row, max_frame, fixed_speed, level_width, level_height, max_health, health, on_ground;
	bool is_animated;
	double current_frame, current_frequency, x_speed, desired_vel, jump_strenght, time;
	ReturnEvents* re;
	Bonus* activate_this_bonus;
	Bonus* active_bonus[3];
	PlayerUI playerUI;
	Player(int _level_width, int _level_height, b2Body * _body, Object * _object, int _health, ReturnEvents* _re);
	void updateUI();
public:
	void activate_bonus(double modificator, BonusType bonus_type);
	void deactivate_bonus(double modificator, BonusType bonus_type);
	void jump();
	void moveLeft();
	void moveRight();
	void stopRight();
	void stopLeft();
	void beginContactWithGround();
	void endContactWithGround();
	Bonus** getActivationBonus();
	void returnCoordinates(double* x, double* y);
	PlayerUI* returnUI();
	bool destroy();
	void update();
};
