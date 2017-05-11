#pragma once
#include "Box2D\Box2D.h"
#include "LevelBox.h"

class DynamicObj
{
protected:
	b2Body* body;
	Object* object;
	int level_width, level_height, delta_x_speed, fixed_speed;
	double x_speed;
	DynamicObj::DynamicObj(int _level_width, int _level_height, b2Body* _body, Object* _object) :
		level_width(_level_width),
		level_height(_level_height),
		body(_body),
		object(_object),
		x_speed(0),
		delta_x_speed(0),
		fixed_speed(10){}
public:
	virtual void contactEvent(b2Contact*, bool)=0;
	virtual void update()=0;
};
