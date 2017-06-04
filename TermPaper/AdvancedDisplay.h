#pragma once
#include "Display.h"

class AdvancedDisplay : public Display
{
	sf::View viewUI;
	sf::Font font;
	sf::Text text;
	sf::Vector2f max_size, min_size;
	void centerView();
	void changeZoom(bool make_closer);
public:
	AdvancedDisplay(Layer* _layer);
	void changeScale(double x, double y);
	void update();
	void handleViewerEvent(ViewEvents ev);
};