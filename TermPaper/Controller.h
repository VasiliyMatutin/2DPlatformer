#pragma once
#include "Events.h"
#include "Model.h"
#include "Viewer.h"

class Controller
{
	sf::RenderWindow* window;
	Model* model;
	Viewer* viewer;
public:
	Controller(Model* _model, Viewer* _viewer);
	void observe();
};
