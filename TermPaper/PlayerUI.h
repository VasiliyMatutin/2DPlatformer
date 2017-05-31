#pragma once
#include "LevelBox.h"

class PlayerUI
{
private:
	std::string player_name;
	std::string player_type;
	Object active_bonuses[3];
	Object health;
	void createBonusUI();
public:
	PlayerUI();
	std::string getPlayerName();
	std::string getPlayerType();
	void setHealthLineImg(int i);
	void setPlayerName(std::string name);
	void setPlayerType(std::string type);
	Object* getActiveBonusesPtr(int number);
	Object* getHealthPtr();
};
