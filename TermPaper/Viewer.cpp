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
}

void Viewer::handleViewerEvent(ViewEvents ev)
{
	switch (ev)
	{
	case ViewEvents::AddLayer:
		prepareNewDisplay();
		break;
	case ViewEvents::DeleteLayer:
		deleteDisplay();
		break;
	case ViewEvents::DistanseZoom:
		display_list.back()->handleViewerEvent(ev);
		break;
	case ViewEvents::BringZoomCloser:
		display_list.back()->handleViewerEvent(ev);
		break;
	}
}

void Viewer::update()
{
	for (auto it : display_list)
	{
		it->update();
	}
}
