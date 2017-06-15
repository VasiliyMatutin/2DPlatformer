/*! \file */

#pragma once
#include <string>

/**
\brief Contains information about tileset images
\author Vasily
\version 1.0
\date June 2017
*/
struct TilesetImg
{
	///number of the first tile in whole row
	int first_gid;
	///number of the last tile in whole row
	int last_gid;
	///number of columns that this tileset contains
	int columns;
};

/**
\brief Contains based information about entity which necessary both for Model and Viewer classes
\author Vasily
\version 1.0
\date June 2017
*/
class Object
{
public:
	///number of the images assigned to this entity in the list of all Layer images
	int number_in_image_list;
	///upper coordinate of an image rectangle in whole image (in pixels)
	int top;
	///left coordinate of an image rectangle in whole image (in pixels)
	int left;
	///x coordinate of an object relatively Layer (in pixels)
	double x;
	///y coordinate of an object relatively Layer (in pixels)
	double y;
	///height of an object (in pixels)
	double height;
	///width of an object (in pixels)
	double width;
	///rotate angle of an object (in radians)
	double rotation;
	///state of an object: 'true' - have to be dispalyed; 'false' - doesnt't have to
	bool is_valid;
	///degree of transparensy (0-fully transperent; 255-fully opaque)
	int transparensy;
};

/**
\brief Contains based information about text entity which necessary both for Model and Viewer classes
\author Vasily
\version 1.0
\date June 2017
*/
class TextObject
{
public:
	///message which should be displayed at monitor
	std::string text;
	///size of the text
	int text_size;
	///x coordinate of an object relatively Layer (in pixels)
	double x;
	///y coordinate of an object relatively Layer (in pixels)
	double y;
};

///coordinates conversion rate from pixels to box2d metrics (meters)
static const int PIXEL_PER_METER = 32;
///conversion rate from degrees to radians 
static const double GRADTORAD = 3.14159265358979323846 / 180;
///conversion rate from radians to degrees 
static const double RADTOGRAD = 1 / GRADTORAD;

