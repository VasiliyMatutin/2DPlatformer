#pragma once
#include "Events.h"
#include "Viewer.h"

class Controller
{
	sf::RenderWindow* window;
	Viewer* viewer;
	Model* model;
	void NotifyViewer();
	void NotifyModel(Events);
public:
	Controller(Viewer*, Model*);
	void observe();
};
