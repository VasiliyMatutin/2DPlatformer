#pragma once

enum class Action
{
	Default,
	Up,
	Down,
	Off
};

class ManualSwitchObj
{
protected:
	bool is_active = false;
public:
	virtual void makeAction(Action);
	virtual bool isActive();
	virtual ~ManualSwitchObj();
};
