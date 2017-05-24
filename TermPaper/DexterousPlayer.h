#pragma once
#include "Player.h"

class DexterousPlayer : public Player
{
public:
	DexterousPlayer(int _level_width, int _level_height, b2Body * _body, Object * _object, int _health);
};
