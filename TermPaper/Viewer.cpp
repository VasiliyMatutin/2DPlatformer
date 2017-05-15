#define _USE_MATH_DEFINES
#include <cmath>
#include "Viewer.h"
#include "WinSingleton.h"

Viewer::Viewer()
{
	window = WinSingleton::getInstance();
	sf::Vector2u win_size = window->getSize();
	view.reset(sf::FloatRect(0, 0, win_size.x, win_size.y));
	max_size.x = win_size.x;
	max_size.y = win_size.y;
	min_size.x = win_size.x / 2;
	min_size.y = win_size.y / 2;
}

void Viewer::setModelPtr(Model * _model)
{
	model = _model;
}

void Viewer::handleViewerEvent(ViewEvents ev)
{
	switch (ev)
	{
	case ViewEvents::Update:
		update();
		break;
	case ViewEvents::LevelCreated:
		prepareNewLevel();
		break;
	case ViewEvents::DistanseZoom:
		changeZoom(false);
		break;
	case ViewEvents::BringZoomCloser:
		changeZoom(true);
		break;
	}
}

void Viewer::prepareNewLevel()
{
	std::vector<std::string>& images = model->returnCurrentLevel()->getImagesList();
	for (int i = 0; i < images.size(); i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile(images[i]);
		tmp.setSmooth(false);
		texture.push_back(tmp);
	}
	std::list<Object>& objects = model->returnCurrentLevel()->getUnchangeableObjectList();
	for (auto it : objects)
	{
		sf::Sprite sprite;
		sprite.setTexture(texture[it.number_in_image_list]);
		sf::Rect<int> rect;
		rect.top = it.top;
		rect.height = it.height;
		rect.left = it.left;
		rect.width = it.width;
		sprite.setTextureRect(rect);
		sprite.setPosition(it.x, it.y);
		sprite.setColor(sf::Color(255, 255, 255));
		constant_sprite.push_back(sprite);
	}
	objects = model->returnCurrentLevel()->getChangeableObjectList();
	for (auto it : objects)
	{
		sf::Sprite sprite;
		sprite.setTexture(texture[it.number_in_image_list]);
		sprite.setColor(sf::Color(255, 255, 255));
		flexible_sprite.push_back(sprite);
	}
}

void Viewer::update()
{
	window->clear();
	for (int i = 0; i < constant_sprite.size(); i++)
		window->draw(constant_sprite[i]);
	std::list<Object>& objects = model->returnCurrentLevel()->getChangeableObjectList();
	int i = 0;
	for (auto it : objects)
	{
		if (it.is_valid)
		{
			sf::Rect<int> rect;
			rect.top = it.top;
			rect.height = it.height;
			rect.left = it.left;
			rect.width = it.width;
			flexible_sprite[i].setOrigin(sf::Vector2f(it.width / 2, it.height / 2));
			flexible_sprite[i].setTextureRect(rect);
			flexible_sprite[i].setPosition(it.x, it.y);
			flexible_sprite[i].setRotation(180 / M_PI * it.rotation);
			window->draw(flexible_sprite[i]);
			i++;
		}
	}
	window->display();
	centerViewOnHero();
	window->setView(view);
}

void Viewer::centerViewOnHero()
{
	double hero_x=0, hero_y=0;
	sf::Vector2f size = view.getSize();
	model->returnCurrentLevel()->returnActivePlayer()->returnCoordinates(&hero_x, &hero_y);
	if (hero_x < size.x / 2)
	{
		hero_x = size.x / 2;
	}
	if (hero_x > max_size.x - size.x / 2)
	{
		hero_x = max_size.x - size.x / 2;
	}
	if (hero_y < size.y / 2)
	{
		hero_y = size.y / 2;
	}
	if (hero_y > max_size.y - size.y / 2)
	{
		hero_y = max_size.y - size.y / 2;
	}
	view.setCenter(hero_x, hero_y);
}

void Viewer::changeZoom(bool make_closer)
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
