#pragma once
#include "AuxiliaryLayer.h"

class GameOver : public AuxiliaryLayer
{
private:
	Object* restart_button;
	Object* quit_button;
	bool is_bad;
public:
	GameOver(bool is_bad);
	void smthHappend(Events what_happened);
};
