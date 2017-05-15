#pragma once
#include "NonStaticObj.h"

class Player : public NonStaticObj
{
private:
	int img_row, max_frame, delta_x_speed, fixed_speed;
	bool is_animated, on_ground;
	double current_frame, current_frequency, x_speed;
public:
	Player(int _max_frame, int _level_width, int _level_height, double _current_frequency, b2Body * _body, Object * _object, int _fixed_speed);
	void jump();
	void moveLeft();
	void moveRight();
	void stopRight();
	void stopLeft();
	void contactEvent(b2Contact * contact, bool is_begin);
	void returnCoordinates(double* x, double* y);
	void update();
};
