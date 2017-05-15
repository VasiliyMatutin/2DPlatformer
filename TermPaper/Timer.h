 #pragma once
#include "ManualSwitchObj.h"
#include "Box2D\Box2D.h"
#include <list>
#include<vector>
#include <chrono>

class Timer
{
private:
	std::list<ManualSwitchObj*> observables;
	std::vector<double> stages_duration;
	std::vector<Action> stages;
	bool is_rounded, is_active;
	double time;
	int curr_iter, stage_iter;
	std::chrono::seconds dts;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> duration;
public:
	Timer(std::list<ManualSwitchObj*> _observables, std::vector<double> _stages_duration, bool _is_rounded, std::vector<Action> _stages);
	void update();
};
