#pragma once
#include "ContactObject.h"
#include "LevelBox.h"

enum class ObjectType
{
	PLAYER,
	BRIDGE_PARTITION,
	PLATFORM,
	BOX
};

class NonStaticObj : public ContactObject
{
protected:
	b2Body* body;
	Object* object;
	bool is_valid;
	ObjectType my_type;
public:
	NonStaticObj(b2Body * _body, Object * _object, ObjectType type);
	void contactEvent(b2Contact*, bool);
	ObjectType whoAmI();
	b2Body* getBody();
	Object* getObject();
	virtual void update();
	virtual bool destroy();
	virtual ~NonStaticObj(){}
};
