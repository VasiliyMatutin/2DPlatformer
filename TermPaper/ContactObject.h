#pragma once
#include "Box2D\Box2D.h"

enum class StaticType
{
	DANGER
};

enum EntityCategory {
	STRONG_PLAYER = 0x0001,
	DEXTEROUS_PLAYER = 0x0002,
	DANGERS = 0x0004,
	OTHERS = 0x0008,
	BONUSES = 0x0010
};

enum EntityGroup {
	MASK_PLAYERS = STRONG_PLAYER | DEXTEROUS_PLAYER,
	MASK_PLAYER = ~MASK_PLAYERS,
    MASK_DANGERS = MASK_PLAYERS,
	MASK_OTHERS = MASK_PLAYERS | OTHERS,
	MASK_BONUSES = MASK_PLAYERS,
};

class ContactObject
{
public:
	virtual void contactEvent(b2Contact*, bool) = 0;
	virtual ~ContactObject(){}
};
