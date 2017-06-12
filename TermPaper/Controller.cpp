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
	viewer->handleViewerEvent(ViewEvents::ADDLAYER);
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
					model->handleEvent(Events::LEFTBUTTON);
					break;
				case sf::Keyboard::Right:
					model->handleEvent(Events::RIGHTBUTTON);
					break;
				case sf::Keyboard::Up:
					model->handleEvent(Events::UPBUTTON);
					break;
				case sf::Keyboard::I:
					model->handleEvent(Events::IBUTTON);
					break;
				case sf::Keyboard::P:
					model->handleEvent(Events::PBUTTON);
					break;
				case sf::Keyboard::C:
					model->handleEvent(Events::CBUTTON);
					break;
				case sf::Keyboard::Escape:
					model->handleEvent(Events::ESCBUTTON);
					break;
				case sf::Keyboard::Return:
					model->handleEvent(Events::ENTERBUTTON);
					break;
				}
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
					model->handleEvent(Events::LEFTBUTTONRELEASED);
					break;
				case sf::Keyboard::Right:
					model->handleEvent(Events::RIGHTBUTTONRELEASED);
					break;
				case sf::Keyboard::Up:
					model->handleEvent(Events::UPBUTTONRELEASED);
					break;
				}
				break;
			case sf::Event::MouseWheelScrolled:
				if (event.mouseWheelScroll.delta < 0)
				{
					viewer->handleViewerEvent(ViewEvents::DISTANCEZOOM);
				}
				else if (event.mouseWheelScroll.delta > 0)
				{
					viewer->handleViewerEvent(ViewEvents::BRINGZOOMCLOSER);
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					MouseClickCoordinates::x = event.mouseButton.x / (double)window->getSize().x * X_WIN_SIZE;
					MouseClickCoordinates::y = event.mouseButton.y / (double)window->getSize().y * Y_WIN_SIZE;
					model->handleEvent(Events::MOUSECLICKED);
				}
				break;
			case sf::Event::Resized:
				viewer->handleViewerEvent(ViewEvents::WINRESIZE);
				break;
			}
		}
		switch (model->checkResponse())
		{
		case ModelReaction::ADD:
			viewer->handleViewerEvent(ViewEvents::ADDLAYER);
			break;
		case ModelReaction::REMOVE:
			viewer->handleViewerEvent(ViewEvents::DELETELAYER);
			break;
		case ModelReaction::CLEARALLANDADD:
			viewer->handleViewerEvent(ViewEvents::DELETEALLLAYERS);
			viewer->handleViewerEvent(ViewEvents::ADDLAYER);
			break;
		case ModelReaction::CLOSE:
			window->close();
			return;
		case ModelReaction::FULLSCREEN:
			WinSingleton::toFullScreen();
			break;
		case ModelReaction::WINDOWED:
			WinSingleton::toWindow();
			break;
		}
		model->update();
		viewer->update();
	}
}
