#pragma once

class ManualSwitchObj
{
protected:
	bool is_active = false;
public:
	virtual void makeAction();
	virtual bool isActive();
	virtual ~ManualSwitchObj();
};
