#include "AdvancedDisplay.h"

void AdvancedDisplay::centerView()
{
	double hero_x = 0, hero_y = 0;
	sf::Vector2f size = view.getSize();
	layer->getLayerCenter(&hero_x, &hero_y);
	if (hero_x < size.x / 2)
	{
		hero_x = size.x / 2;
	}
	else if (hero_x > max_size.x - size.x / 2)
	{
		hero_x = max_size.x - size.x / 2;
	}
	if (hero_y < size.y / 2)
	{
		hero_y = size.y / 2;
	}
	else if (hero_y > max_size.y - size.y / 2)
	{
		hero_y = max_size.y - size.y / 2;
	}
	view.setCenter(hero_x, hero_y);
}

void AdvancedDisplay::changeZoom(bool make_closer)
{
	sf::Vector2f size = view.getSize();
	if (make_closer)
	{
		if (size.y >= min_size.y && size.x >= min_size.x)
		{
			view.zoom(0.99f);
		}
	}
	else
	{
		if (size.y <= max_size.y - 10 && size.x <= max_size.x - 10)
		{
			view.zoom(1.0100f);
		}
	}
}

AdvancedDisplay::AdvancedDisplay(Layer* _layer) : Display(_layer)
{
	sf::Vector2u win_size = window->getSize();
	viewUI.reset(sf::FloatRect(0, 0, win_size.x, win_size.x));
	font.loadFromFile("Fonts/CyrilicOld.ttf");
	text.setFillColor(sf::Color::Black);
	text.setFont(font);
	max_size.x = win_size.x;
	max_size.y = win_size.y;
	min_size.x = win_size.x / 2;
	min_size.y = win_size.y / 2;
}

void AdvancedDisplay::update()
{
	centerView();
	Display::updateWithoutDisplay();
	window->setView(viewUI);
	std::list<Object*> objects = layer->getUIObjects();
	for (auto it : objects)
	{
		if (it->is_valid == true)
		{
			window->draw(setSprite(*it));
		}
	}
	std::list<TextObject*> text_objects = layer->getTextObjects();
	for (auto it : text_objects)
	{
		text.setString(it->text);
		text.setCharacterSize(it->text_size);
		text.setPosition(it->x, it->y);
		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		window->draw(text);
	}
	window->display();
}

void AdvancedDisplay::handleViewerEvent(ViewEvents ev)
{
	switch (ev)
	{
	case ViewEvents::DistanseZoom:
		changeZoom(false);
		break;
	case ViewEvents::BringZoomCloser:
		changeZoom(true);
		break;
	}
}
