#pragma once
#include "ContactObject.h"
#include "NonStaticObj.h"
#include <list>

class MyContactListener : public b2ContactListener
{
private:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
	std::list<NonStaticObj*> to_destroy_list;
public:
	std::list<NonStaticObj*>* getToDestroyListPtr();
}; 
