#pragma once
#include <SFML/Graphics.hpp>

struct TilesetImg
{
	int first_gid, last_gid, columns, rows;
	sf::Texture img;
};

struct Layer
{
	int opacity;
	std::vector<sf::Sprite> tiles;
};
