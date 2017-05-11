#pragma once
#include <string>

struct TilesetImg
{
	int first_gid, last_gid, columns;
};

struct Object
{
	bool is_valid = 1;
	int number_in_image_list, top, height, left, width;
	double x, y;
};
