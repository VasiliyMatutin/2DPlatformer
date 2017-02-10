#pragma once
#include "Box2D\Box2D.h"
#include "LevelBox.h"

class DynamicObj
{
	b2Body* body;
	Object* object;
	int img_row, max_frame, level_width, level_height, delta_x_speed, fixed_speed;
	bool on_ground, is_animated;
	double current_frame, current_frequency, x_speed;
public:
	DynamicObj(int, int, int, double, b2Body*, Object*);
	void moveLeft();
	void stopLeft();
	void moveRight();
	void stopRight();
	void contactEvent(b2Contact*, bool);
	void jump();
	void update();
};
