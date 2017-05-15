#pragma once
#include <string>
#

struct TilesetImg
{
	int first_gid, last_gid, columns;
};

struct Object
{
	bool is_valid = 1;
	int number_in_image_list, top, left;
	double x, y, height, width, rotation;
};

static const int PIXEL_PER_METER = 32;
static const double GRADTORAD = 3.14159265358979323846 / 180;
static const double RADTOGRAD = 1 / GRADTORAD;

