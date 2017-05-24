#pragma once
#include "NonStaticObj.h"

enum class Sides
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

class Player : public NonStaticObj
{
protected:
	int img_row, left_row, right_row, max_frame, fixed_speed, level_width, level_height, health, on_ground;
	bool is_animated;
	double current_frame, current_frequency, x_speed, desired_vel, jump_strenght;
	Player(int _level_width, int _level_height, b2Body * _body, Object * _object, int _health);
public:
	void jump();
	void moveLeft();
	void moveRight();
	void stopRight();
	void stopLeft();
	void decreaseHealth(int _healt_loss);
	void beginContactWithGround();
	void endContactWithGround();
	void returnCoordinates(double* x, double* y);
	void update();
};
