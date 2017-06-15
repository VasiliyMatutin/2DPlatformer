#include "Timer.h"

Timer::Timer(std::list<ManualSwitchObj*> _observables, std::vector<double> _stages_duration, bool _is_rounded, std::vector<Action> _stages, std::chrono::duration<double>* _duration):
	observables(_observables),
	stages_duration(_stages_duration),
	is_rounded(_is_rounded),
	stages(_stages),
	duration(_duration),
	is_active(1),
	curr_iter(0),
	stage_iter(0)
{
	start = *duration;
	if (stages_duration.empty())
	{
		is_active = false;
	}
	if (stages.empty())
	{
		stages.push_back(Action::DEFAULT);
	}
}

void Timer::update()
{
	if (!is_active)
	{
		return;
	}
	dts = std::chrono::duration_cast<std::chrono::seconds>(*duration - start);
	time = dts.count();
	if (time >= stages_duration[curr_iter])
	{
		for (auto it : observables)
		{
			it->makeAction(stages[stage_iter]);
		}
		if (stage_iter == stages.size() - 1)
		{
			stage_iter = -1;
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
		stage_iter++;
		start = *duration;
	}
}
