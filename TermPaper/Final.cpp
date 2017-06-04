#include "Final.h"

void Final::contactEvent(b2Contact * contact, bool is_begin)
{
	if (is_begin)
	{
		is_contact = 1;
	}
	else
	{
		is_contact = 0;
	}
}

Final::Final(b2Body * body, bool is_strong) :
	is_contact(false)
{
	body->SetUserData(this);
	b2Filter filter;
	if (is_strong)
	{
		filter.categoryBits = OTHERS;
		filter.maskBits = STRONG_PLAYER;
	}
	else
	{
		filter.categoryBits = OTHERS;
		filter.maskBits = DEXTEROUS_PLAYER;
	}
	body->GetFixtureList()->SetFilterData(filter);
}

bool Final::isReach()
{
	return is_contact;
}
