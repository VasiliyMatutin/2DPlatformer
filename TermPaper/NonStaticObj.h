#pragma once
#include "ContactObject.h"
#include "LevelBox.h"

enum class ObjectCategory {
	DESTROYABLE,
	NONDESTROYABLE
};

class NonStaticObj : public ContactObject
{
protected:
	b2Body* body;
	Object* object;
public:
	NonStaticObj(b2Body * _body, Object * _object);
	void contactEvent(b2Contact*, bool);
	virtual void update();
	virtual bool destroy(b2World* lvl_world);
	virtual ~NonStaticObj(){}
	virtual ObjectCategory getObjCategory()
	{
		return ObjectCategory::NONDESTROYABLE;
	}
};
