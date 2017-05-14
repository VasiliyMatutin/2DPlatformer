#pragma once
#include "Box2D\Box2D.h"

class ContactObject
{
public:
	virtual void contactEvent(b2Contact*, bool) = 0;
	virtual ~ContactObject()
	{

	}
};
