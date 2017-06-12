/*! \file */

/**
\brief "Game Over" screen
\author Vasily
\version 1.0
\date June 2017

Stores information needed to display "Game Over" or "You win" screen
*/

#pragma once
#include "AuxiliaryLayer.h"

class GameOver : public AuxiliaryLayer
{
private:
	///Pointer to object contain button "Restart"
	Object* restart_button;
	///Pointer to object contain button "Quit"
	Object* quit_button;
	/*!
	\brief Define type of the screen
	\param false "You win" screen
	\param true "Game over" screen
	*/
	bool is_bad;
public:
	/*!
	\param is_bad set the type of the screen (see is_bad private flag)
	*/
	GameOver(bool is_bad);
	/*!
	\brief Listener of player action

	Virtual method, inhereted from Layer class, which allow react to user action
	\param what_happened enum describing player action
	*/
	void smthHappend(Events what_happened);
};
