#pragma once
#include "Display.h"

class AdvancedDisplay : public Display
{
	sf::View viewUI;
	sf::Font font;
	sf::Text text;
	sf::Vector2f max_size, min_size;
	std::vector<sf::Texture> texture;
	void centerView();
	void changeZoom(bool make_closer);
public:
	AdvancedDisplay(Layer* _layer);
	virtual void update();
	virtual void handleViewerEvent(ViewEvents ev);
};