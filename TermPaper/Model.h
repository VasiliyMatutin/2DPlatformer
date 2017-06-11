#pragma once
#include "Level.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "LocalMenu.h"
#include "Events.h"
#include "EndOfTheGame.h"
#include "ErrorWindow.h"
#include <stack>

class Model
{
	ReturnEvents* re;
	MainMenu main_menu;
	GameOver game_over;
	GameOver win;
	LocalMenu local_menu;
	EndOfTheGame eotg;
	ErrorWindow ew;
	int current_level;
	std::vector<std::string> level_dir;
	std::vector<std::string> level_names;
	std::stack<Layer*> layers_list;
	void clearAllLayers();
public:
	Model();
	void handleEvent(Events);
	void update();
	Layer* returnUpperLayer();
	ModelReaction checkResponse();
};