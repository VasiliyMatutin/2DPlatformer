#pragma once
#include "Model.h"

class Viewer
{
	Model* model;
	sf::RenderWindow* window;
public:
	Viewer(Model*);
	void update();
};
