/*! \file */

/**
\brief "Main menu" screen
\author Vasily
\version 1.0
\date June 2017

Stores information needed to display "Main menu"
*/

#pragma once
#include "AuxiliaryLayer.h"

class MainMenu : public AuxiliaryLayer
{
private:
	///Title of the game
	TextObject introduction;
	///Pointer to object contain button "Start"
	Object* start_button;
	///Pointer to object contain button "Exit"
	Object* exit_button;
	///Pointer to object contain button "Fullscreen"
	Object* f_mode_button;
	///Pointer to object contain button "Windowed"
	Object* w_mode_button;
	/*!
	\brief Define which button active now
	\param false "Windowed" button active
	\param true "Fullscreen" button active
	*/
	bool fs;
public:
	///Default constructor
	MainMenu();
	/*!
	\brief Listener of player action

	Virtual method, inhereted from Layer class, which allow react to user action
	\param what_happened enum describing player action
	*/
	void smthHappend(Events what_happened);
	/*!
	\brief Check the entry of a coordinate into an object (button default)

	Special function to dynamic object which origin is their center, not an left-top corner (diff. from isContains in AuxiliaryLayer class) 
	\param x x coordinate
	\param y y coordinate
	\param button object to check
	*/
	bool isContainsC(double x, double y, Object * button);
};
