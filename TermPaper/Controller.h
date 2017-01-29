#pragma once
#include "Events.h"
#include "Model.h"
#include "Viewer.h"

class Controller
{
	sf::RenderWindow* window;
	Model model;
	Viewer viewer;
	void NotifyModel(Events);
public:
	Controller();
	void observe();
};
