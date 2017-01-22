#include "Model.h"

void Model::handleEvent(Events _event)
{
	switch (_event)
	{
	case LoadLevel:
		current_level.loadLevel("Test.tmx");
	}
}

Level * Model::returnCurrentLevel()
{
	return &current_level;
}
