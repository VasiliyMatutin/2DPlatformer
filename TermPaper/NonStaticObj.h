/*! \file */

#pragma once
#include "ContactObject.h"
#include "LevelBox.h"

///Define the type of an object of an NonStaticObj class for dynamic box2d objects
enum class ObjectType
{
	PLAYER, ///<it's hero object
	BRIDGE_PARTITION,///it's drawbridge or partition
	PLATFORM,///it's platform 
	BOX///it's box (doesn't matter metal or wooden)
};

/**
\brief Typical object (an entity) that participates in physics simulation
\author Vasily
\version 1.0
\date June 2017

An entity that have only base properties (can't be controlled by the player, fully rely on box2d world rules)
*/
class NonStaticObj : public ContactObject
{
protected:
	///pointer to the box2d body assigned to this entity
	b2Body* body;
	///pointer to the Object class assigned to this entity
	Object* object;
	///defines the state of the entity 'true' - participate in physics simulation 'false' - doesn't paticipate
	bool is_valid;
	///define type of an dynamic object assigned to this entity
	ObjectType my_type;
	///inherited from ContactObject class
	void contactEvent(b2Contact* contact, bool is_begin);
public:
	/*!
	\brief Defined constructor for this class
	\param _body pointer to the box2d body assigned to this entity
	\param _object pointer to the Object class assigned to this entity
	\param type type from ObjectType enum of an assigned dynamic object
	*/
	NonStaticObj(b2Body * _body, Object * _object, ObjectType type);
	/*!
	\brief Allow to define type of an assigned dynamic object
	\return type from ObjectType enum of an assigned dynamic object
	*/
	ObjectType whoAmI();
	/*!
	\return pointer to the box2d body assigned to this entity
	*/
	b2Body* getBody();
	/*!
	\return pointer to the Object class assigned to this entity
	*/
	Object* getObject();
	///update entity state (position in the world, speed etc.)
	virtual void update();
	/// destroy the entity
	virtual bool destroy();
	virtual ~NonStaticObj(){}
};
