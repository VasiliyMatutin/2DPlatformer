/*! \file */

/**
\brief Drawbridge which can be activated by the sensor
\author Vasily
\version 1.0
\date June 2017
*/

#pragma once
#include "ManualSwitchObj.h"
#include "NonStaticObj.h"

class RevoluteBridge : public NonStaticObj, public ManualSwitchObj
{
private:
	///speed of bridge rotation
	double motor_speed;
	///pointer to the box2d joint where bridge pin to the world ground
	b2RevoluteJoint* joint;
	///define joint existense 'true' - exist; 'false' - dosen't exist
	bool is_joint_exist;
public:
	/*!
	\brief Defined constructor for this class
	\param _body pointer to the box2d body assigned to this bridge
	\param _object pointer to the Object class assigned to this bridge
	\param _bridge_joint pointer to the Viewer class, which will use in MVC model
	\param _motor_speed speed of bridge rotation
	*/
	RevoluteBridge(b2Body* _body, Object* _object, b2RevoluteJoint* _bridge_joint, double _motor_speed);
	///inhereted from ManualSwitchObj class
	void makeAction(Action action);
	///inhereted from NonStaticObj class
	bool destroy();
	///inhereted from NonStaticObj class
	void update();
};
