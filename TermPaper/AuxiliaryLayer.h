/*! \file */

/**
\brief Superstructure class for built-in Layer classes
\author Vasily
\version 1.0
\date June 2017

Provides functions which necessary for built-in Layer classes such as main menu, end of the game screen etc.
*/

#pragma once
#include "Layer.h"

class AuxiliaryLayer : public Layer
{
protected:
	///Default constructor
	AuxiliaryLayer() {};
	/*!
	\brief Check the entry of a coordinate into an object (button default)
	\param x x coordinate
	\param y y coordinate
	\param button object to check
	*/
	virtual bool isContains(double x, double y, Object * button);
public:
	virtual ~AuxiliaryLayer() {};
};
