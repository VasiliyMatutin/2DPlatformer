#pragma once
#include "Box2D\Box2D.h"
#include "LevelBox.h"

class DynamicObj
{
	b2Body* body;
	Object* object;
	int img_row, max_frame, level_width, level_height, x_speed;
	bool is_move;
	double current_frame, current_frequency;
public:
	DynamicObj(int, int, int, double, b2Body*, Object*);
	void moveLeft();
	void moveRight();
	void jump();
	void stop();
	void update();
};
