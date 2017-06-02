#pragma once
#include "Level.h"
#include "Events.h"
#include <stack>

class Model
{
	ReturnEvents re;
	int level_width, level_height;
	std::stack<Layer*> layers_list;
public:
	Model();
	void handleEvent(Events);
	void update();
	Layer* returnUpperLayer();
};