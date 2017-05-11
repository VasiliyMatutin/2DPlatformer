#include "Viewer.h"
#include "WinSingleton.h"

Viewer::Viewer()
{
	window = WinSingleton::getInstance();
}

void Viewer::setModelPtr(Model * _model)
{
	model = _model;
}

void Viewer::handleViewerEvent(ViewEvents ev)
{
	switch (ev)
	{
	case Update:
		update();
		break;
	case LevelCreated:
		prepareNewLevel();
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
			flexible_sprite[i].setTextureRect(rect);
			flexible_sprite[i].setPosition(it.x - it.width/2, it.y - it.height/2);
			window->draw(flexible_sprite[i]);
			i++;
		}
	}
	window->display();
}
