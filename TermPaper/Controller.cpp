#include "Controller.h"
#include "WinSingleton.h"
#include <iostream>
#include <chrono>

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
	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	std::chrono::duration<double> frequency(0.001);
	NotifyModel(LoadLevel);
	viewer.handleViewerEvent(LevelCreated);
	sf::Event event;
	window->setKeyRepeatEnabled(false); // To disable repeated KeyPressed events
	while (window->isOpen())
	{
		if (std::chrono::system_clock::now() - start > frequency)
		{
			start = std::chrono::system_clock::now();
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
						model.handleEvent(StopHeroMoveLeft);
						break;
					case sf::Keyboard::Right:
						model.handleEvent(StopHeroMoveRight);
						break;
					case sf::Keyboard::Up:
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
}
