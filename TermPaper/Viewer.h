#pragma once
#include <SFML/Graphics.hpp>
#include "Model.h"

class Viewer
{
	Model* model;
	sf::RenderWindow* window;
	std::vector<sf::Sprite> constant_sprite;
	std::vector<sf::Sprite> flexible_sprite;
	std::vector<sf::Texture> texture;
	void prepareNewLevel();
	void update();
public:
	Viewer();
	void setModelPtr(Model*);
	void handleViewerEvent(ViewEvents);
};
