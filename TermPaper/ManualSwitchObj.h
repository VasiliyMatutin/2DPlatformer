/*! \file */

#pragma once

///type of action that observables entity have to make
enum class Action
{
	DEFAULT, ///< action at discretio of the observable entity
	UP, ///< move up
	DOWN, ///< move down
	OFF ///< terminate moving
};

/**
\brief Based entity for objects that can be activated by the sensor
\author Vasily
\version 1.0
\date June 2017
*/
class ManualSwitchObj
{
protected:
	///defines the state of the object 'true' - moves 'false' - doesn't move
	bool is_active = false;
public:
	/*!
	\brief causes the object to make some action
	\param action what necessary to make
	*/
	virtual void makeAction(Action action);
	/*!
	\brief defines the state of the object
	\return 'true' - moves 'false' - doesn't move
	*/
	virtual bool isActive();
	virtual ~ManualSwitchObj();
};
