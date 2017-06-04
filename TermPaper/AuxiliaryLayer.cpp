#include "AuxiliaryLayer.h"

bool AuxiliaryLayer::isContains(double x, double y, Object * button)
{
	if (x > button->x &&
		x < button->x + button->width &&
		y > button->y &&
		y < button->y + button->height)
	{
		return true;
	}
	return false;
}
