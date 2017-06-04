#pragma once
#include "Layer.h"

class AuxiliaryLayer : public Layer
{
protected:
	virtual bool isContains(double x, double y, Object * button);
};
