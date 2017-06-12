/*! \file */

/**
\brief Operating element in MVC structure
\author Vasily
\version 1.0
\date June 2017

Processes SFML-window events and provides
		 communication between Viewer and Model classes
*/

#pragma once
#include "Viewer.h"

class Controller
{
	///Pointer to the instance window of the game
	sf::RenderWindow* window;
	///Pointer to the Model class
	Model* model;
	///Pointer to the Viewer class
	Viewer* viewer;
public:
	/*!
	\brief Defined constructor for this class
	\param _model pointer to the Model class, which will use in MVC model
	\param _viewer pointer to the Viewer class, which will use in MVC model
	*/
	Controller(Model* _model, Viewer* _viewer);
	///Start the game life cycle
	void observe();
};
