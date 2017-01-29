#pragma once
#include "Level.h"
#include "Events.h"

class Model
{
	int level_width, level_height;
	Level current_level;
public:
	Model();
	void handleEvent(Events);
	Level* returnCurrentLevel();
};