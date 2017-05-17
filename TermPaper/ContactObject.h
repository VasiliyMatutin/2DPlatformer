#pragma once
#include "Box2D\Box2D.h"

enum EntityCategory {
	PLAYER = 0x0001,
};

class ContactObject
{
public:
	virtual void contactEvent(b2Contact*, bool) = 0;
	virtual ~ContactObject(){}
};
