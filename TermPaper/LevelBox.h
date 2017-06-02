#pragma once
#include <string>

struct TilesetImg
{
	int first_gid, last_gid, columns;
};

class Object
{
public:
	int number_in_image_list;
	int top;
	int left;
	double x;
	double y;
	double height;
	double width;
	double rotation;
	bool is_valid;
};

class TextObject
{
public:
	std::string text;
	int text_size;
	double x;
	double y;
};

static const int PIXEL_PER_METER = 32;
static const double GRADTORAD = 3.14159265358979323846 / 180;
static const double RADTOGRAD = 1 / GRADTORAD;

