#include "ManualSwitchObj.h"

void ManualSwitchObj::makeAction()
{
	is_active = !is_active;
}

bool ManualSwitchObj::isActive()
{
	return is_active;
}

ManualSwitchObj::~ManualSwitchObj()
{
}
