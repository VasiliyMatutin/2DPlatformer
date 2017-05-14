#include "Model.h"

Model::Model(){}

void Model::handleEvent(Events _event)
{
	switch (_event)
	{
	case Events::LoadLevel:
		current_level.loadLevel("Test.tmx");
		break;
	case Events::HeroMoveLeft:
		current_level.returnActivePlayer()->moveLeft();
		break;
	case Events::HeroMoveRight:
		current_level.returnActivePlayer()->moveRight();
		break;
	case Events::Jumping:
		current_level.returnActivePlayer()->jump();
		break;
	case Events::StopHeroMoveLeft:
		current_level.returnActivePlayer()->stopLeft();
		break;
	case Events::StopHeroMoveRight:
		current_level.returnActivePlayer()->stopRight();
		break;
	case Events::SwitchLever:
		current_level.tryToSwitchLever();
		break;
	case Events::Move:
		current_level.update();
		break;
	}
}

Level * Model::returnCurrentLevel()
{
	return &current_level;
}
