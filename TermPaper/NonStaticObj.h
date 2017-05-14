#pragma once
#include "ContactObject.h"
#include "LevelBox.h"

class NonStaticObj : public ContactObject
{
protected:
	b2Body* body;
	Object* object;
	int level_width, level_height, fixed_speed;
	NonStaticObj::NonStaticObj(int _level_width, int _level_height, b2Body* _body, Object* _object, int _fixed_speed) :
		level_width(_level_width),
		level_height(_level_height),
		body(_body),
		object(_object),
		fixed_speed(_fixed_speed){}
public:
	void contactEvent(b2Contact*, bool)=0;
	virtual void update()=0;
	virtual ~NonStaticObj()
	{

	}
};
