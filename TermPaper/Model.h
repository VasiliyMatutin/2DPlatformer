/*! \file */

/**
\brief Element-container in MVC structure
\author Vasily
\version 1.0
\date June 2017

Contain necessary information and change state depending on controller commands
*/

#pragma once
#include "Level.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "LocalMenu.h"
#include "Events.h"
#include "EndOfTheGame.h"
#include "ErrorWindow.h"
#include <stack>

class Model
{
	///class with information needed to display "Main menu"
	MainMenu main_menu;
	///class with information needed to display "Game over"
	GameOver game_over;
	///class with information needed to display "You win"
	GameOver win;
	///class with information needed to display "Local menu"
	LocalMenu local_menu;
	///class with information needed to display "The end"
	EndOfTheGame eotg;
	///class with information needed to display "Error"
	ErrorWindow ew;
	///current level number among all levels in the list
	int current_level;
	///vector with paths to images file
	std::vector<std::string> level_dir;
	///vector with paths to the level file
	std::vector<std::string> level_names;
	///stack for game-state managment (react only top Layer)
	std::stack<Layer*> layers_list;
	///clear stack
	void clearAllLayers();
public:
	///Default constructor
	Model();
	~Model();
	/*!
	\brief causes Model to react on Controller command
	\param event Controller command in enum Events form
	*/
	void handleEvent(Events event);
	///causes Model to update state
	void update();
	/*!
	\return top layer at 'layers_list'
	*/
	Layer* returnUpperLayer();
	/*!
	\return reaction of the model to the last Controller command or update action
	*/
	ModelReaction checkResponse();
};