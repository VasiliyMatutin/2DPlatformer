#pragma once
#include "Level.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "LocalMenu.h"
#include "Events.h"
#include "EndOfTheGame.h"
#include <stack>

class Model
{
	ReturnEvents* re;
	MainMenu main_menu;
	GameOver game_over;
	GameOver win;
	LocalMenu local_menu;
	EndOfTheGame eotg;
	int current_level;
	std::vector<std::string> level_names;
	std::stack<Layer*> layers_list;
public:
	Model();
	void handleEvent(Events);
	void update();
	Layer* returnUpperLayer();
	ReturnEvents checkResponse();
};