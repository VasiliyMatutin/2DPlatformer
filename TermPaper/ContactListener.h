/*! \file */

/**
\brief Override for standart box2d ContactListener
\author Vasily
\version 1.0
\date June 2017
*/

#pragma once
#include "NonStaticObj.h"
#include <list>

class MyContactListener : public b2ContactListener
{
private:
	///Override standart box2d function (see box2d man)
	void BeginContact(b2Contact* contact);
	///Override standart box2d function (see box2d man)
	void EndContact(b2Contact* contact);
	///Override standart box2d function (see box2d man)
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
	///List, containing pointer level objects, which will be destroy after the end of box2d world simulation at the next update iteration
	std::list<NonStaticObj*> to_destroy_list;
public:
	/*!
	\param return pointer to the 'to_destroy_list' 
	*/
	std::list<NonStaticObj*>* getToDestroyListPtr();
}; 
