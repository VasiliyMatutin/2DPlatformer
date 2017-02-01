#include "Controller.h"
#include "WinSingleton.h"

Controller::Controller()
{
	window = WinSingleton::getInstance();
	viewer.setModelPtr(&model);
}

void Controller::NotifyModel(Events _event)
{
	model.handleEvent(_event);
}


void Controller::observe()
{
	NotifyModel(LoadLevel);
	viewer.handleViewerEvent(LevelCreated);
	sf::Event event;
	while (window->isOpen())
	{
		if (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
					model.handleEvent(HeroMoveLeft);
					break;
				case sf::Keyboard::Right:
					model.handleEvent(HeroMoveRight);
					break;
				case sf::Keyboard::Up:
					model.handleEvent(Jumping);
					break;
				case sf::Keyboard::Escape:
					window->close();
					break;
				}
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
					model.handleEvent(StopHero);
					break;
				case sf::Keyboard::Right:
					model.handleEvent(StopHero);
					break;
				}
				break;
			}
		}
		model.handleEvent(Move);
		viewer.handleViewerEvent(Update);
	}
}
