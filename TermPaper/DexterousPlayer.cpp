#include "DexterousPlayer.h"

DexterousPlayer::DexterousPlayer(int _level_width, int _level_height, b2Body * _body, Object * _object, int _health) : Player(_level_width, _level_height, _body, _object, _health)
{
	max_frame = 3;
	fixed_speed = 4;
	right_row = 2;
	left_row = 1;
	jump_strenght = 5.5;
}
