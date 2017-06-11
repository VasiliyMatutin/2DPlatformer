#include "Layer.h"

Layer::Layer()
{
	re = ReturnEvents::DEFAULT;
}

std::list<Object> Layer::getUnchangeableObjects()
{
	return unchangeable_objects;
}

std::list<Object> Layer::getChangeableObjects()
{
	return changeable_objects;
}

std::list<Object*> Layer::getUIObjects()
{
	return UI_objects;
}

std::list<TextObject*> Layer::getTextObjects()
{
	return text_objects;
}

void Layer::getLayerSize(double * width, double * height)
{
	*width = 800;
	*height = 600;
}

void Layer::getLayerCenter(double * x, double * y)
{
	*x = 0;
	*y = 0;
}

bool Layer::isDoubleView()
{
	return false;
}

void Layer::repause()
{
}

void Layer::update()
{
}

std::vector<std::string>& Layer::getImagesList()
{
	return images;
}

ReturnEvents* Layer::getRetEvent()
{
	return &re;
}
