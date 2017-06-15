/*! \file */

/**
\brief Provides a display for Layer information
\author Vasily
\version 1.0
\date June 2017
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "Layer.h"

class Display
{
protected:
	///pointer to the Layer with model information to display
	Layer* layer;
	///pointer to the singletone application window
	sf::RenderWindow* window;
	///base view for elements at the level
	sf::View view;
	///text font
	sf::Font font;
	///sfml text container
	sf::Text text;
	///vector containing sfml sprites for non-changeable elements
	std::vector<sf::Sprite> constant_sprite;
	///vector containing sfml textures for all Layer's images
	std::vector<sf::Texture> texture;
	/*!
	\brief internal function which fill sfml sprite with information from Object class

	IT'S IMPORTANT! Sprite origin is the left-top point of an object
	\param it Object with information
	\return created sfml sprite
	*/
	sf::Sprite setSprite(Object it);
	/*!
	\brief internal function which fill sfml sprite with information from Object class

	IT'S IMPORTANT! Sprite origin is the center of an object
	\param it Object with information
	\return created sfml sprite
	*/
	sf::Sprite setDynamicSprite(Object it);
	///prepare class for work
	void loadDisplay();
	///special update without text information (which doesn't display)
	void updateWithoutText();
public:
	/*!
	\brief Defined constructor for this class
	\param _layer container which contain model information for display
	*/
	Display(Layer* _layer);
	virtual ~Display() {};
	///change scale of the screen
	virtual void changeScale();
	/*!
	\brief provide display reaction on user action and model changes (command from Controller)
	\param event command from Controller
	*/
	virtual void handleViewerEvent(ViewEvents event);
	///update information on the screen
	virtual void update();
};