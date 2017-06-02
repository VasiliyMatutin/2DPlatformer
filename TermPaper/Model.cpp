#include "Model.h"

Model::Model()
{
	Level* test_level = new Level(std::string("test.tmx"));
	layers_list.push(test_level);
}

void Model::handleEvent(Events _event)
{
	layers_list.top()->smthHappend(_event);
}

void Model::update()
{
	re = ReturnEvents::DEFAULT;
	layers_list.top()->update();
	switch (re)
	{
	case ReturnEvents::DEFAULT:
		return;
	}
}

Layer * Model::returnUpperLayer()
{
	return layers_list.top();
}
