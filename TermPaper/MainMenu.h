#pragma once
#include "AuxiliaryLayer.h"

class MainMenu : public AuxiliaryLayer
{
private:
	Object* start_button;
	Object* exit_button;
public:
	MainMenu();
	void smthHappend(Events what_happened);
};
