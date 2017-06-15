/*! \file */

/**
\brief Special sensor which define end of the level (win position)
\author Vasily
\version 1.0
\date June 2017
*/

#pragma once
#include "Player.h"

class Final : public ContactObject
{
private:
	///pointer to the player which have to gain this point
	Player* my_player;
	///define achive the player, who intended to gain this point, its goal or not: 'true' - achive; 'false' - doesn't achive
	bool is_contact;
	///define type of the player intended to gain this point: 'true' - strong player; 'false' - dexterous player
	bool is_strong;
	///inherited from ContactObject class
	void contactEvent(b2Contact* contact, bool is_begin);
public:
	/*!
	\brief Defined constructor for this class
	\param is_strong define type of the player intended to gain this point: 'true' - strong player; 'false' - dexterous player
	\param body pointer to the box2d body assigned to this final point
	*/
	Final(b2Body* body, bool is_strong);
	/*!
	\brief Define achive the player, who intended to gain this point, its goal or not
	\return 'true' - achive; 'false' - doesn't achive
	*/
	bool isReach();
};
