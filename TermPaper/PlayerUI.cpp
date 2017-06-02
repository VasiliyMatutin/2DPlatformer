#include "PlayerUI.h"

void PlayerUI::createBonusUI()
{
	for (int i = 0; i < 3; ++i)
	{
		Object tmp_obj;
		tmp_obj.top = 0;
		tmp_obj.left = 0;
		tmp_obj.x = 32 * i + 20;
		tmp_obj.y = 75;
		tmp_obj.rotation = 0;
		tmp_obj.height = 32;
		tmp_obj.width = 32;
		tmp_obj.is_valid = false;
		active_bonuses[i] = tmp_obj;
	} 
}

PlayerUI::PlayerUI()
{
	createBonusUI();
}

TextObject* PlayerUI::getPlayerName()
{
	return &player_name;
}

TextObject* PlayerUI::getPlayerType()
{
	return &player_type;
}

void PlayerUI::setHealthLineImg(int i)
{
	health.number_in_image_list = i;
}

void PlayerUI::setPlayerName(std::string name)
{
	player_name.text = name;
	player_name.x = 70;
	player_name.y = 20;
	player_name.text_size = 24;
}

void PlayerUI::setPlayerType(std::string type)
{
	player_type.text = type;
	player_type.x = 70;
	player_type.y = 38;
	player_type.text_size = 16;
}

Object * PlayerUI::getActiveBonusesPtr(int number)
{
	return &active_bonuses[number];
}

Object * PlayerUI::getHealthPtr()
{
	return &health;
}
