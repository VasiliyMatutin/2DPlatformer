#include "Model.h"

Model::Model(){}

void Model::handleEvent(Events _event)
{
	switch (_event)
	{
	case LoadLevel:
		current_level.loadLevel("Test.tmx");
		break;
	case HeroMoveLeft:
		current_level.returnActivePlayer()->moveLeft();
		break;
	case HeroMoveRight:
		current_level.returnActivePlayer()->moveRight();
		break;
	case Jumping:
		current_level.returnActivePlayer()->jump();
		break;
	case StopHeroMoveLeft:
		current_level.returnActivePlayer()->stopLeft();
		break;
	case StopHeroMoveRight:
		current_level.returnActivePlayer()->stopRight();
		break;
	case Move:
		current_level.update();
	}
}

Level * Model::returnCurrentLevel()
{
	return &current_level;
}
