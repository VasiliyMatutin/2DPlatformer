#pragma once
#include "Box2D\Box2D.h"
#include "DynamicObj.h"

class MyContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
}; 