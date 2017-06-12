/*! \file */

/**
\brief Special sensor for character
\author Vasily
\version 1.0
\date June 2017

Allow define position of the hero  relatively the ground (see on_ground in Player class)
*/

#pragma once
#include "ContactObject.h"
#include "Player.h"

class PlayerSensor : public ContactObject
{
private:
	///the number of active contact
	int contact_count;
	///pointer to the player object to which this sensor is attached
	Player* player;
public:
	/*!
	\brief Defined constructor for this class
	\param observable_player pointer to the Player class to which body this sensor is attached
	\param _body pointer to the box2d body assigned to this sensor
	*/
	PlayerSensor(Player* observable_player, b2Body* body);
	///inhereted from ContactObject
	void contactEvent(b2Contact * contact, bool is_begin);
};
