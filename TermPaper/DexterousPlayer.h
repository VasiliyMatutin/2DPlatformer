/*! \file */

/**
\brief Contains information about dexterous characret
\author Vasily
\version 1.0
\date June 2017
*/

#pragma once
#include "Player.h"

class DexterousPlayer : public Player
{
public:
	/*!
	\brief Defined constructor for this class
	\param _level_width the width in pixels of this level
	\param _level_height the height in pixels of this level
	\param _body pointer to the box2d body assigned to this character
	\param _object pointer to the Object class assigned to this character
	\param _health the maximum level of health reserve for this caracter
	\param _re pointer to the variable which contains reply of the current level during last iteration (see Layer class)
	*/
	DexterousPlayer(int _level_width, int _level_height, b2Body * _body, Object * _object, int _health, ReturnEvents* _re);
};
