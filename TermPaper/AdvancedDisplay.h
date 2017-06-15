/*! \file */

/**
\brief Provides a dual-view display for Layer information
\author Vasily
\version 1.0
\date June 2017
*/

#pragma once
#include "Display.h"

class AdvancedDisplay : public Display
{
	///view for UI elements at the level
	sf::View viewUI;
	///contains maximum size of the base(main) view in x & y coordinates
	sf::Vector2f max_size;
	///contains minimum size of the base(main) view in x & y coordinates
	sf::Vector2f min_size;
	///heigth of the layer
	double l_heigth;
	///width of the layer
	double l_width;
	///internal function which moves the view according to the hero coordinates
	void centerView();
	/*!
	\brief make view closer or postpone it
	\param make_closer define what need to do: 'true' - make closer; 'false' - postpone
	*/
	void changeZoom(bool make_closer);
public:
	/*!
	\brief Defined constructor for this class
	\param _layer container which contain model information for display
	*/
	AdvancedDisplay(Layer* _layer);
	///inherited from Display
	void changeScale();
	///inherited from Display
	void update();
	///inherited from Display
	void handleViewerEvent(ViewEvents ev);
};