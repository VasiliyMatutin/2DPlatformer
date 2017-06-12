/*! \file */

/**
\brief "The End" screen
\author Vasily
\version 1.0
\date June 2017

Stores information needed to display "The End" screen
*/

#pragma once
#include "AuxiliaryLayer.h"

class EndOfTheGame : public AuxiliaryLayer
{
private:
	///Pointer to object contain button "quit"
	Object* quit_button;
public:
	///Default constructor
	EndOfTheGame();
	/*!
	\brief Listener of player action

	Virtual method, inhereted from Layer class, which allow react to user action
	\param what_happened enum describing player action
	*/
	void smthHappend(Events what_happened);
};