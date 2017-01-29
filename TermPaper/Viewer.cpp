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
	std::vector<Object>& objects = model->returnCurrentLevel()->getUnchangeableObjectList();
	for (int i = 0; i < objects.size(); i++)
	{
		sf::Sprite sprite;
		sprite.setTexture(texture[objects[i].number_in_image_list]);
		sf::Rect<int> rect;
		rect.top = objects[i].top;
		rect.height = objects[i].height;
		rect.left = objects[i].left;
		rect.width = objects[i].width;
		sprite.setTextureRect(rect);
		sprite.setPosition(objects[i].x, objects[i].y);
		sprite.setColor(sf::Color(255, 255, 255));
		constant_sprite.push_back(sprite);
	}
	objects = model->returnCurrentLevel()->getChangeableObjectList();
	for (int i = 0; i < objects.size(); i++)
	{
		sf::Sprite sprite;
		sprite.setTexture(texture[objects[i].number_in_image_list]);
		sprite.setColor(sf::Color(255, 255, 255));
		flexible_sprite.push_back(sprite);
	}
}

void Viewer::update()
{
	window->clear();
	for (int i = 0; i < constant_sprite.size(); i++)
		window->draw(constant_sprite[i]);
	std::vector<Object>& objects = model->returnCurrentLevel()->getChangeableObjectList();
	for (int i = 0; i < flexible_sprite.size(); i++)
	{
		if (objects[i].is_valid)
		{
			sf::Rect<int> rect;
			rect.top = objects[i].top;
			rect.height = objects[i].height;
			rect.left = objects[i].left;
			rect.width = objects[i].width;
			flexible_sprite[i].setTextureRect(rect);
			flexible_sprite[i].setPosition(objects[i].x - objects[i].width/2, objects[i].y - objects[i].height/2);
			window->draw(flexible_sprite[i]);
		}
	}
	window->display();
}
