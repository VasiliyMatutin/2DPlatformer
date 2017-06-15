/*! \file */

/**
\brief Viewer-element in MVC structure
\author Vasily
\version 1.0
\date June 2017

Provides display tools
*/

#pragma once
#include "AdvancedDisplay.h"
#include "Model.h"
#include <list>

class Viewer
{
	///pointer to the model where information is stored
	Model* model;
	///pointer to the singletone application window
	sf::RenderWindow* window;
	///list of active displays
	std::list <Display*> display_list;
	///create new display
	void prepareNewDisplay();
	///delete display from the head of the list
	void deleteDisplay();
public:
	/*!
	\brief Defined constructor for this class
	\param model pointer to the model where information is stored
	*/
	Viewer(Model* model);
	~Viewer();
	///update information in all displays
	void update();
	/*!
	\brief provide displays reaction on user action and model changes (command from Controller)
	\param event command from Controller
	*/
	void handleViewerEvent(ViewEvents event);
};
