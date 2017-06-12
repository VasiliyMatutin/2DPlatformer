#include "Model.h"
#include <fstream>

void Model::clearAllLayers()
{
	while (!layers_list.empty())
	{
		if (layers_list.top()->isDoubleView())
		{
			delete layers_list.top();
		}
		layers_list.pop();
	}
}

Model::Model() :
	game_over(true),
	win(false),
	current_level(-1)
{
	{
		std::ifstream fin("Levels/levels_list.txt");
		for (std::string line; std::getline(fin, line); )
		{
			level_dir.push_back(line);
			std::getline(fin, line);
			level_names.push_back(line + ".tmx");
		}
	}
	layers_list.push(&main_menu);
	re = layers_list.top()->getRetEvent();
}

Model::~Model()
{
	clearAllLayers();
}

void Model::handleEvent(Events _event)
{
	layers_list.top()->smthHappend(_event);
}

void Model::update()
{
	layers_list.top()->update();
}

Layer * Model::returnUpperLayer()
{
	return layers_list.top();
}

ModelReaction Model::checkResponse()
{
	ReturnEvents re = *(layers_list.top()->getRetEvent());
	*(layers_list.top()->getRetEvent()) = ReturnEvents::DEFAULT;
	switch (re)
	{
	case ReturnEvents::DEFAULT:
		break;
	case ReturnEvents::NEXTLEVEL:
	{
		clearAllLayers();
		current_level++;
		if (current_level + 1 > level_names.size())
		{
			layers_list.push(&eotg);
			current_level = 0;
			return ModelReaction::CLEARALLANDADD;
		}
		try
		{
			Level* test_level = new Level(level_dir[current_level], level_names[current_level]);
			layers_list.push(test_level);
		}
		catch (std::string ex)
		{
			if (current_level + 2 > level_names.size())
			{
				current_level = 0;
			}
			else
			{
				current_level++;
			}
			clearAllLayers();
			ew.setErrorMsg(ex);
			layers_list.push(&ew);
			return ModelReaction::CLEARALLANDADD;
		}
		return ModelReaction::CLEARALLANDADD;
	}
	case ReturnEvents::CLOSELOCALMENU:
	{
		layers_list.pop();
		layers_list.top()->repause();
		return ModelReaction::REMOVE;
	}
	case ReturnEvents::OPENMENU:
	{
		current_level--;
		clearAllLayers();
		layers_list.push(&main_menu);
		return ModelReaction::CLEARALLANDADD;
	}
	case ReturnEvents::OPENLOCALMENU:
	{
		layers_list.push(&local_menu);
		return ModelReaction::ADD;
	}
	break;
	case ReturnEvents::RESTART:
	{
		clearAllLayers();
		Level* test_level = new Level(level_dir[current_level], level_names[current_level]);
		layers_list.push(test_level);
		return ModelReaction::CLEARALLANDADD;
	}
	case ReturnEvents::WIN:
	{
		layers_list.push(&win);
		return ModelReaction::ADD;
	}
	case ReturnEvents::GAMEOVER:
	{
		layers_list.push(&game_over);
		return ModelReaction::ADD;
	}
	case ReturnEvents::CLOSE:
		return ModelReaction::CLOSE;
	case ReturnEvents::FULLSCREEN:
		return ModelReaction::FULLSCREEN;
	case ReturnEvents::WINDOWED:
		return ModelReaction::WINDOWED;
	}
	return ModelReaction::NOTHING;
}
