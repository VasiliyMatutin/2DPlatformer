#pragma once
#include "LevelBox.h"

class PlayerUI
{
private:
	TextObject player_name;
	TextObject player_type;
	Object active_bonuses[3];
	Object health{ 0, 0, 0, 28, 52, 10, 99, 0, true };
	void createBonusUI();
public:
	PlayerUI();
	TextObject* getPlayerName();
	TextObject* getPlayerType();
	void setHealthLineImg(int i);
	void setPlayerName(std::string name);
	void setPlayerType(std::string type);
	Object* getActiveBonusesPtr(int number);
	Object* getHealthPtr();
};
