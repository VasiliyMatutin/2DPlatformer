#pragma once
#include "Box2D\Box2D.h"
#include "LevelBox.h"

class DynamicObj
{
	b2Body* body;
	Object* object;
	int img_row, max_frame;
	bool is_move;
	double current_frame, current_frequency;
public:
	DynamicObj(int, double, b2Body*, Object*);
	void moveLeft();
	void moveRight();
	void stop();
	void update();
};
