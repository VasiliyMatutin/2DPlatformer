#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "LevelBox.h"

class Level
{
	int level_width, level_height, tile_width, tile_height;
	std::vector <TilesetImg> image_list;
	std::vector<Layer> layer_list;
public:
	Level();
	bool loadLevel(std::string filename);
	std::vector<Layer>& getLayerList();
};
