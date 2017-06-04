#pragma once
#include "AuxiliaryLayer.h"

class EndOfTheGame : public AuxiliaryLayer
{
private:
	Object* quit_button;
public:
	EndOfTheGame();
	void smthHappend(Events what_happened);
};