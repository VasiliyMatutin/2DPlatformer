#include "DexterousPlayer.h"

DexterousPlayer::DexterousPlayer(int _level_width, int _level_height, b2Body * _body, Object * _object, int _health, ReturnEvents* _re) : Player(_level_width, _level_height, _body, _object, _health, _re)
{
	max_frame = 3;
	fixed_speed = 4;
	right_row = 2;
	left_row = 1;
	jump_strenght = 5.5;
	Player::playerUI.setPlayerName("Player1");
	Player::playerUI.setPlayerType("\"Fast and Furious\"");
	b2Filter filter = body->GetFixtureList()->GetFilterData();
	filter.categoryBits = DEXTEROUS_PLAYER;
	filter.maskBits = MASK_PLAYER;
	body->GetFixtureList()->SetFilterData(filter);
}
