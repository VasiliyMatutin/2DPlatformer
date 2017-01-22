#include "Level.h"
#include "tinyxml2.h"
#include <iostream>
#include <sstream>

Level::Level()
{
}

bool Level::loadLevel(std::string filename)
{
	image_list.clear();

	//load XML-file with level description
	tinyxml2::XMLDocument level_file;
	tinyxml2::XMLError error = level_file.LoadFile(filename.c_str());

	//Error verification
	if (error != 0)
	{
		std::cout << "Loading level \"" << filename << "\" failed." << std::endl; ///Exeptions!!!! Won't forget!!
		return false;
	}

	//Set map parameters
	tinyxml2::XMLElement *map = level_file.FirstChildElement("map");
	level_width = atoi(map->Attribute("width"));
	level_height = atoi(map->Attribute("height"));
	tile_width = atoi(map->Attribute("tilewidth"));
	tile_height = atoi(map->Attribute("tileheight"));

	//Add tileset image
	TilesetImg tg;
	tinyxml2::XMLElement *tileset = map->FirstChildElement("tileset");
	while (tileset)
	{
		tg.first_gid = atoi(tileset->Attribute("firstgid"));
		tg.columns = atoi(tileset->Attribute("columns"));
		tg.last_gid = tg.first_gid + atoi(tileset->Attribute("tilecount")) - 1;
		tinyxml2::XMLElement *image;
		image = tileset->FirstChildElement("image");
		tg.img.loadFromFile(std::string(image->Attribute("source")));
		tg.img.setSmooth(false);
		tg.rows = tg.img.getSize().y / tile_height;
		image_list.push_back(tg);
		tileset = tileset->NextSiblingElement("tileset");
	}

	//Add layers
	tinyxml2::XMLElement *layer = map->FirstChildElement("layer");
	while (layer)
	{
		Layer tmp_layer;
		if (layer->Attribute("opacity")) tmp_layer.opacity = 255 * atoi(layer->Attribute("opacity"));
		else tmp_layer.opacity = 255;

		//Read tiles in CSV
		tinyxml2::XMLElement *data = layer->FirstChildElement("data");
		const char* str=data->GetText();
		std::stringstream tempss;
		tempss << str;
		sf::Sprite sprite;
		int i,j, x=0, y=0;
		while (tempss >> i)
		{
			j = 0;
			while (j < image_list.size())
			{
				if (i >= image_list[j].first_gid && i <= image_list[j].last_gid)
				{
					int current_gid = i - image_list[j].first_gid;
					sprite.setTexture(image_list[j].img);
					sf::Rect<int> rect;
					rect.top = current_gid / image_list[j].columns * tile_height;
					rect.height = tile_height;
					rect.left = current_gid % image_list[j].columns * tile_width;
					rect.width = tile_width;
					sprite.setTextureRect(rect);
					sprite.setPosition(x * tile_width, y * tile_height);
					sprite.setColor(sf::Color(255, 255, 255, tmp_layer.opacity));
					tmp_layer.tiles.push_back(sprite);
					break;
				}
				j++;
			}
			x++;
			if (x >= level_width)
			{
				x = 0;
				y++;
			}
			if (tempss.peek() == ',') tempss.ignore();
		}
		layer_list.push_back(tmp_layer);
		layer = layer->NextSiblingElement("layer");
	}
	return 1;
}

std::vector<Layer>& Level::getLayerList()
{
	return layer_list;
}
