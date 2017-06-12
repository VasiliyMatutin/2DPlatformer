/*! \file */

#pragma once
#include "Box2D\Box2D.h"
/// Bitmask for objects, participating box2d collision
enum EntityCategory {
	STRONG_PLAYER = 0x0001, ///< Mask for strong player
	DEXTEROUS_PLAYER = 0x0002, ///< Mask for dexterous player
	DANGERS = 0x0004, ///< Mask for kinematic danger objects
	OTHERS = 0x0008, ///< Mask for all other objects
	BONUSES = 0x0010 ///< Mask for bonus objects
};

/// Bitmask-rule for box2d collision
enum EntityGroup {
	MASK_PLAYERS = STRONG_PLAYER | DEXTEROUS_PLAYER, ///< Mask for players
	MASK_PLAYER = ~MASK_PLAYERS, ///< Rule for players
    MASK_DANGERS = MASK_PLAYERS, ///< Rule for kinematic danger objects
	MASK_OTHERS = MASK_PLAYERS | OTHERS, ///< Rule for all other objects
	MASK_BONUSES = MASK_PLAYERS, ///< Rule for bonus objects
};

/**
\brief Interface for an object which can collide with another in box2d world
\author Vasily
\version 1.0
\date June 2017
*/
class ContactObject
{
public:
	/*!
	\brief Define object reaction to the collision in box2d world
	\param contact pointer to box2d b2Contact class
	\param isBegin 'false' - end of the collision; 'true' - start of the collision
	*/
	virtual void contactEvent(b2Contact* contact, bool isBegin) = 0;
	virtual ~ContactObject(){}
};
