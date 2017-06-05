#include "Model.h"
#include <fstream>

Model::Model() :
	game_over(true),
	win(false),
	current_level(-1)
{
	{
		std::ifstream fin("Levels/levels_list.txt");
		for (std::string line; std::getline(fin, line); )
		{
			level_names.push_back("Levels/" + line + ".tmx");
		}
	}
	layers_list.push(&main_menu);
	re = layers_list.top()->getRetEvent();
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

ReturnEvents Model::checkResponse()
{
	ReturnEvents re = *(layers_list.top()->getRetEvent());
	*(layers_list.top()->getRetEvent()) = ReturnEvents::DEFAULT;
	switch (re)
	{
	case ReturnEvents::DEFAULT:
		break;
	case ReturnEvents::NEXTLEVEL:
	{
		layers_list.pop();
		current_level++;
		if (current_level + 1 > level_names.size())
		{
			while (!layers_list.empty())
			{
				layers_list.pop();
			}
			layers_list.push(&eotg);
			current_level = -1;
			return ReturnEvents::OPENMENU;
		}
		Level* test_level = new Level(std::string(level_names[current_level]));
		layers_list.push(test_level);
		break;
	}
	case ReturnEvents::CLOSELOCALMENU:
	{
		layers_list.pop();
		break;
	}
	case ReturnEvents::OPENMENU:
	{
		while (!layers_list.empty())
		{
			layers_list.pop();
		}
		layers_list.push(&main_menu);
		current_level = -1;
		break;
	}
	case ReturnEvents::OPENLOCALMENU:
	{
		layers_list.push(&local_menu);
		return ReturnEvents::NEXTLEVEL;
	}
	break;
	case ReturnEvents::RESTART:
	{
		while (!layers_list.empty())
		{
			layers_list.pop();
		}
		Level* test_level = new Level(std::string(level_names[current_level]));
		layers_list.push(test_level);
		return ReturnEvents::OPENMENU;
	}
	case ReturnEvents::WIN:
	{
		layers_list.push(&win);
		return ReturnEvents::NEXTLEVEL;
	}
	case ReturnEvents::GAMEOVER:
	{
		layers_list.push(&game_over);
		return ReturnEvents::NEXTLEVEL;
	}
	case ReturnEvents::CLOSE:
		break;
	}
	return re;
}
