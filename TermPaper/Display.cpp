#include "Display.h"
#include "WinSingleton.h"

sf::Sprite Display::setSprite(Object it)
{
	sf::Sprite sprite;
	sprite.setColor(sf::Color(255, 255, 255, it.transparensy));
	if (it.height != 0)
	{
		sf::Rect<int> rect;
		rect.top = it.top;
		rect.height = it.height;
		rect.left = it.left;
		rect.width = it.width;
		sprite.setTextureRect(rect);
	}
	sprite.setTexture(texture[it.number_in_image_list]);
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

void Display::updateWithoutText()
{
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
	font.loadFromFile("Fonts/CyrilicOld.ttf");
	text.setFillColor(sf::Color::Black);
	text.setFont(font);
	window = WinSingleton::getInstance();
	sf::Vector2u win_size = window->getSize();
	double l_heigth, l_width;
	layer->getLayerSize(&l_width, &l_heigth);
	view.reset(sf::FloatRect(0, 0, (win_size.x<l_width) ? win_size.x : l_width, (win_size.y<l_heigth) ? win_size.y : l_heigth));
	loadDisplay();
}

void Display::changeScale()
{
}

void Display::handleViewerEvent(ViewEvents)
{
}

void Display::update()
{
	updateWithoutText();
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
