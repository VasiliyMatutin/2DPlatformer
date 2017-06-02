#include "Display.h"
#include "WinSingleton.h"

sf::Sprite Display::setSprite(Object it)
{
	sf::Sprite sprite;
	sprite.setColor(sf::Color(255, 255, 255));
	sf::Rect<int> rect;
	rect.top = it.top;
	rect.height = it.height;
	rect.left = it.left;
	rect.width = it.width;
	sprite.setTexture(texture[it.number_in_image_list]);
	sprite.setTextureRect(rect);
	sprite.setPosition(it.x, it.y);
	return sprite;
}

sf::Sprite Display::setDynamicSprite(Object it)
{
	sf::Sprite sprite = setSprite(it);
	sprite.setOrigin(sf::Vector2f(it.width / 2, it.height / 2));
	sprite.setRotation(RADTOGRAD * it.rotation);
	return (sprite);
}

void Display::loadDisplay()
{
	std::vector<std::string>& images = layer->getImagesList();
	for (int i = 0; i < images.size(); ++i)
	{
		sf::Texture tmp;
		tmp.loadFromFile(images[i]);
		tmp.setSmooth(false);
		texture.push_back(tmp);
	}
	std::list<Object>& objects = layer->getUnchangeableObjects();
	for (auto it : objects)
	{
		constant_sprite.push_back(setSprite(it));
	}
}

void Display::updateWithoutDisplay()
{
	window->clear();
	window->setView(view);
	for (auto it : constant_sprite)
	{
		window->draw(it);
	}
	std::list<Object>& objects = layer->getChangeableObjects();
	for (auto it : objects)
	{
		if (it.is_valid)
		{
			window->draw(setDynamicSprite(it));
		}
	}
}

Display::Display(Layer * _layer):
	layer(_layer)
{
	window = WinSingleton::getInstance();
	sf::Vector2u win_size = window->getSize();
	view.reset(sf::FloatRect(0, 0, win_size.x, win_size.y));
	loadDisplay();
}

void Display::handleViewerEvent(ViewEvents)
{
}

void Display::update()
{
	updateWithoutDisplay();
	window->display();
}
