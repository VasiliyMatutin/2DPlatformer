/*! \file */

/**
\brief An entity that can activate observables ManualSwitchObj classes at a certain moment (dosen't display at the monitor)
\author Vasily
\version 1.0
\date June 2017
*/

#pragma once
#include "ManualSwitchObj.h"
#include "Box2D\Box2D.h"
#include <list>
#include<vector>
#include <chrono>

class Timer
{
private:
	///list of observables objects
	std::list<ManualSwitchObj*> observables;
	///vector of duration intervals between commands
	std::vector<double> stages_duration;
	///vector of stages(commands) through which observables objects should pass
	std::vector<Action> stages;
	///defines should timer resume the cycle then all iterasion has been passed: 'true' - should; 'false' -shouldn't
	bool is_rounded;
	///defines is active timer now or already completed its work
	bool is_active;
	///current time from the previous interval
	double time;
	///number of current interval from stages_duration vector
	int curr_iter;
	///number of current stage from stages vector
	int stage_iter;
	///chrono service information
	std::chrono::seconds dts;
	///pointer to the variable containing information about level time
	std::chrono::duration<double>* duration;
	///chrono start of impact
	std::chrono::duration<double> start;
public:
	/*!
	\brief Defined constructor for this class
	\param _observables list of observables objects
	\param _stages_duration vector of duration intervals between commands
	\param _is_rounded defines should timer resume the cycle then all iterasion has been passed: 'true' - should; 'false' -shouldn't
	\param _stages vector of stages(commands) through which observables objects should pass
	\param _duration pointer to the variable containing information about level time
	*/
	Timer(std::list<ManualSwitchObj*> _observables, std::vector<double> _stages_duration, bool _is_rounded, std::vector<Action> _stages, std::chrono::duration<double>* _duration);
	///update timer state (remaining time before next iteration)
	void update();
};