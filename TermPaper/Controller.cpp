#include "Controller.h"
#include "WinSingleton.h"

Controller::Controller(Model* _model, Viewer* _viewer):
	model(_model),
	viewer(_viewer)
{
	window = WinSingleton::getInstance();
}


void Controller::observe()
{
	viewer->handleViewerEvent(ViewEvents::AddLayer);
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
					model->handleEvent(Events::LeftButton);
					break;
				case sf::Keyboard::Right:
					model->handleEvent(Events::RightButton);
					break;
				case sf::Keyboard::Up:
					model->handleEvent(Events::UpButton);
					break;
				case sf::Keyboard::I:
					model->handleEvent(Events::IButton);
					break;
				case sf::Keyboard::P:
					model->handleEvent(Events::PButton);
					break;
				case sf::Keyboard::C:
					model->handleEvent(Events::CButton);
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
					model->handleEvent(Events::LeftButtonReleased);
					break;
				case sf::Keyboard::Right:
					model->handleEvent(Events::RightButtonReleased);
					break;
				case sf::Keyboard::Up:
					model->handleEvent(Events::UpButtonReleased);
					break;
				}
				break;
			case sf::Event::MouseWheelScrolled:
				if (event.mouseWheelScroll.delta < 0)
				{
					viewer->handleViewerEvent(ViewEvents::DistanseZoom);
				}
				else if (event.mouseWheelScroll.delta > 0)
				{
					viewer->handleViewerEvent(ViewEvents::BringZoomCloser);
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					MouseClickCoordinates::x = event.mouseButton.x;
					MouseClickCoordinates::y = event.mouseButton.y;
					model->handleEvent(Events::MouseClicked);
				}
			}
		}
		model->update();
		viewer->update();
	}
}
