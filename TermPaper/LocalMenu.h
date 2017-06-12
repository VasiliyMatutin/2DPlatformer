/*! \file */

/**
\brief "Local menu" screen
\author Vasily
\version 1.0
\date June 2017

Stores information needed to display "Local menu" screen at the level
*/

#pragma once
#include "AuxiliaryLayer.h"

class LocalMenu : public AuxiliaryLayer
{
private:
	///Pointer to object contain button "Restart"
	Object* restart_button;
	///Pointer to object contain button "Quit"
	Object* quit_button;
	///Pointer to object contain button "Resume"
	Object* resume_button;
public:
	///Default constructor
	LocalMenu();
	/*!
	\brief Listener of player action

	Virtual method, inhereted from Layer class, which allow react to user action
	\param what_happened enum describing player action
	*/
	void smthHappend(Events what_happened);
};