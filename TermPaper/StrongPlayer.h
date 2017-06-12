/*! \file */

/**
\brief Contains information about strong characret
\author Vasily
\version 1.0
\date June 2017
*/

#pragma once
#include "Player.h"

class StrongPlayer : public Player
{
private:
	///pointer to box2d joint which created when hero raises an box
	b2Joint* joint;
	///pointer to box2d body of raised box
	b2Body* box;
	///maximum box2d impulse below which hero can carry a box (in other words max mass of the box)
	double box_coef;
	///define joint existense 'true' - hero carry a box; 'false' - hero dosen't carry the box
	bool is_joint_set;
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
	StrongPlayer(int _level_width, int _level_height, b2Body * _body, Object * _object, int _health, ReturnEvents* _re);
	///causes the hero to try pick up the box
	void tryToPickupBox();
	/*!
	\brief set throwing direction of the box
	\param x x coordinate of the direction (will be normalized)
	\param y y coordinate of the direction (will be normalized)
	*/
	void throwBox(double x, double y);
	///inhereted from Player
	void update();
};
