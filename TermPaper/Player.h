#pragma once
#include "DynamicObj.h"

class Player : public DynamicObj
{
private:
	int img_row, max_frame;
	bool on_ground, is_animated;
	double current_frame, current_frequency;
public:
	Player(int _max_frame, int _level_width, int _level_height, double _current_frequency, b2Body * _body, Object * _object);
	void jump();
	void moveLeft();
	void moveRight();
	void stopRight();
	void stopLeft();
	void contactEvent(b2Contact * contact, bool is_begin);
	void update();
};
