#include "Controller.h"
#include "WinSingleton.h"

void Controller::NotifyViewer()
{
	viewer->update();
}

void Controller::NotifyModel(Events _event)
{
	model->handleEvent(_event);
}

Controller::Controller(Viewer * _viewer, Model * _model)
{
	viewer = _viewer;
	model = _model;
	window = WinSingleton::getInstance();
}

void Controller::observe()
{
	NotifyModel(LoadLevel);
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		NotifyViewer();
	}
}
