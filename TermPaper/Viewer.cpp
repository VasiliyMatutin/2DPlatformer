#include "Viewer.h"
#include "WinSingleton.h"

void Viewer::prepareNewDisplay()
{
	if (model->returnUpperLayer()->isDoubleView())
	{
		display_list.push_back(new AdvancedDisplay(model->returnUpperLayer()));
	}
	else
	{
		display_list.push_back(new Display(model->returnUpperLayer()));
	}
}

void Viewer::deleteDisplay()
{
	delete display_list.back();
	display_list.pop_back();
}

Viewer::Viewer(Model * _model) :
	model(_model)
{
	window = WinSingleton::getInstance();
}

Viewer::~Viewer()
{
	for (auto it : display_list)
	{
		delete it;
	}
}

void Viewer::handleViewerEvent(ViewEvents ev)
{
	switch (ev)
	{
	case ViewEvents::ADDLAYER:
		prepareNewDisplay();
		break;
	case ViewEvents::DELETEALLLAYERS:
		for (auto it : display_list)
		{
			delete it;
		}
		display_list.clear();
		break;
	case ViewEvents::DELETELAYER:
		deleteDisplay();
		break;
	case ViewEvents::DISTANCEZOOM:
		display_list.back()->handleViewerEvent(ev);
		break;
	case ViewEvents::BRINGZOOMCLOSER:
		display_list.back()->handleViewerEvent(ev);
		break;
	case ViewEvents::WINRESIZE:
		if (!display_list.empty())
		{
			display_list.back()->changeScale(window->getSize().x / X_WIN_SIZE, window->getSize().y / Y_WIN_SIZE);
		}
		break;
	}
}

void Viewer::update()
{
	window->clear();
	for (auto it : display_list)
	{
		it->update();
	}
	window->display();
}
