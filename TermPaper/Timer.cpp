#include "Timer.h"

Timer::Timer(std::list<ManualSwitchObj*> _observables, std::vector<double> _stages_duration, bool _is_rounded):
	observables(_observables),
	stages_duration(_stages_duration),
	is_rounded(_is_rounded),
	is_active(1),
	curr_iter(0)
{
	start = std::chrono::system_clock::now();
	if (stages_duration.empty())
	{
		is_active = false;
	}
}

void Timer::update()
{
	if (!is_active)
	{
		return;
	}
	end = std::chrono::system_clock::now();
	duration = end - start;
	dts = std::chrono::duration_cast<std::chrono::seconds>(duration);
	time = dts.count();
	if (time >= stages_duration[curr_iter])
	{
		for (auto it : observables)
		{
			it->makeAction();
		}
		if (curr_iter == stages_duration.size() - 1)
		{
			if (is_rounded)
			{
				curr_iter = -1;
			}
			else
			{
				is_active = false;
				return;
			}
		}
		curr_iter++;
		start = std::chrono::system_clock::now();
	}
}
