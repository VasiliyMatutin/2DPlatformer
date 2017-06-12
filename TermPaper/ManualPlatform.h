/*! \file */

/**
\brief Platform that can be activated by the sensor
\author Vasily
\version 1.0
\date June 2017
*/

#pragma once
#include "Platform.h"
#include "ManualSwitchObj.h"

class ManualPlatform : public Platform, public ManualSwitchObj
{
private:
	///store backup of the current node of the trajectory for this platform
	int backup_counter = 0;
public:
	/*!
	\brief Defined constructor for this class
	\param _level_width the width in pixels of this level
	\param _level_height the height in pixels of this level
	\param _body pointer to the box2d body assigned to this platform
	\param _object pointer to the Object class assigned to this platform
	\param _traj_coord set of the trajectory coordinates for this platform
	\param _fixed_speed speed of the platform
	\param _is_rounded defines the shape of trajectory 'true' - closed 'false' - torn
	\param _node_number max number of trajectory nodes which platform passed before reverse moving or the stop
	*/
	ManualPlatform(int _level_width, int _level_height, b2Body* _body, Object* _object, std::vector<std::pair<double, double>> traj_coord, int _fixed_speed, bool _is_rounded, int _node_number);
	///inherited from Platform class
	void update();
	/*!
	\brief causes the bridge to make some action
	\param action what necessary to make (doesn't matter; always Action::default is expected)
	*/
	void makeAction(Action);
	/*!
	\return pointer to the box2d body assigned to this platform
	*/
	b2Body* getBody();
	/*!
	\return pointer to the Object class assigned to this platform
	*/
	Object* getObject();
};
