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
	NotifyModel(Events::LoadLevel);
	viewer.handleViewerEvent(ViewEvents::LevelCreated);
	sf::Event event;
	window->setKeyRepeatEnabled(false); // To disable repeated KeyPressed events
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
					model.handleEvent(Events::HeroMoveLeft);
					break;
				case sf::Keyboard::Right:
					model.handleEvent(Events::HeroMoveRight);
					break;
				case sf::Keyboard::Up:
					model.handleEvent(Events::Jumping);
					break;
				case sf::Keyboard::I:
					model.handleEvent(Events::SwitchLever);
					break;
				case sf::Keyboard::P:
					model.handleEvent(Events::PickUp);
					break;
				case sf::Keyboard::C:
					model.handleEvent(Events::ChangeHero);
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
					model.handleEvent(Events::StopHeroMoveLeft);
					break;
				case sf::Keyboard::Right:
					model.handleEvent(Events::StopHeroMoveRight);
					break;
				case sf::Keyboard::Up:
					model.handleEvent(Events::StopHero);
					break;
				}
				break;
			case sf::Event::MouseWheelScrolled:
				if (event.mouseWheelScroll.delta < 0)
				{
					viewer.handleViewerEvent(ViewEvents::DistanseZoom);
				}
				else if (event.mouseWheelScroll.delta > 0)
				{
					viewer.handleViewerEvent(ViewEvents::BringZoomCloser);
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					MouseClickCoordinates::x = event.mouseButton.x;
					MouseClickCoordinates::y = event.mouseButton.y;
					model.handleEvent(Events::MouseClicked);
				}
			}
		}
		model.handleEvent(Events::Move);
		viewer.handleViewerEvent(ViewEvents::Update);
	}
}
