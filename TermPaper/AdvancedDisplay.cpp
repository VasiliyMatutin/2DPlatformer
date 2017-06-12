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
	else if (hero_x > l_width - size.x / 2)
	{
		hero_x = l_width - size.x / 2;
	}
	if (hero_y < size.y / 2)
	{
		hero_y = size.y / 2;
	}
	else if (hero_y > l_heigth - size.y / 2)
	{
		hero_y = l_heigth - size.y / 2;
	}
	view.setCenter(hero_x, hero_y);
	layer->getLayerCenter(&hero_x, &hero_y);
	PositionRelativelyScreen::x = hero_x - view.getCenter().x + (view.getSize().x/2) / (double)window->getSize().x * X_WIN_SIZE;
	PositionRelativelyScreen::y = hero_y - view.getCenter().y + (view.getSize().y/2) / (double)window->getSize().y * Y_WIN_SIZE;
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
	min_size.x = 400;
	min_size.y = 300;
	sf::Vector2u win_size = window->getSize();
	layer->getLayerSize(&l_width, &l_heigth);
	max_size.x = (win_size.x < l_width) ? win_size.x : l_width;
	max_size.y = (win_size.y < l_heigth) ? win_size.y : l_heigth;
	viewUI.reset(sf::FloatRect(0, 0, max_size.x, max_size.y));
}

void AdvancedDisplay::changeScale(double x, double y)
{
	sf::Vector2u win_size = window->getSize();
	layer->getLayerSize(&l_width, &l_heigth);
	max_size.x = (win_size.x < l_width) ? win_size.x : l_width;
	max_size.y = (win_size.y < l_heigth) ? win_size.y : l_heigth;
	view.reset(sf::FloatRect(0, 0, max_size.x, max_size.y));
	viewUI.reset(sf::FloatRect(0, 0, max_size.x, max_size.y));
}

void AdvancedDisplay::update()
{
	centerView();
	updateWithoutText();
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
}

void AdvancedDisplay::handleViewerEvent(ViewEvents ev)
{
	switch (ev)
	{
	case ViewEvents::DISTANCEZOOM:
		changeZoom(false);
		break;
	case ViewEvents::BRINGZOOMCLOSER:
		changeZoom(true);
		break;
	}
}
