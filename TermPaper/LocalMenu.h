#pragma once
#include "AuxiliaryLayer.h"

class LocalMenu : public AuxiliaryLayer
{
private:
	Object* restart_button;
	Object* quit_button;
	Object* resume_button;
public:
	LocalMenu();
	void smthHappend(Events what_happened);
};