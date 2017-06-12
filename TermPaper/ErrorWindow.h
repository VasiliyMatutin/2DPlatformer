/*! \file */

/**
\brief "The Error" screen
\author Vasily
\version 1.0
\date June 2017

Stores information needed to display "The Error" screen
*/

#pragma once
#include "AuxiliaryLayer.h"

class ErrorWindow : public AuxiliaryLayer
{
private:
	///Heading of the screen
	TextObject introduction;
	///Error message
	TextObject error_msg;
	///Recommendation for user to contact developer
	TextObject conclusion;
	///Pointer to object contain button "OK"
	Object* ok_button;
public:
	///Default constructor
	ErrorWindow();
	/*!
	\brief Set error message to display
	\param error_msg string containing error message
	*/
	void setErrorMsg(std::string error_msg);
	/*!
	\brief Listener of player action

	Virtual method, inhereted from Layer class, which allow react to user action
	\param what_happened enum describing player action
	*/
	void smthHappend(Events what_happened);
};
