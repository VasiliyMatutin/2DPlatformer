#pragma once
#include "Level.h"
#include "Events.h"

class Model
{
	Level current_level;
public:
	Model() {};
	void handleEvent(Events);
	Level* returnCurrentLevel();
};