#pragma once
#include "AdvancedDisplay.h"
#include "Model.h"
#include <list>

class Viewer
{
	Model* model;
	std::list <Display*> display_list;
	void prepareNewDisplay();
	void deleteDisplay();
public:
	Viewer(Model* model);
	void update();
	void handleViewerEvent(ViewEvents);
};
