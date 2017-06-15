/*! \file */

/**
\brief Kinematic object moving along the trajectory
\author Vasily
\version 1.0
\date June 2017
*/

#pragma once
#include <vector>
#include "NonStaticObj.h"

class Platform : public NonStaticObj
{
protected:
	///set of the trajectory coordinates for this platform 
	std::vector<std::pair<double, double>> coord_set;
	///current node of the trajectory for this platform
	int point_iter;
	///current increment or decrement of point_iter
	int incr;
	///max number of trajectory nodes which platform passed before reverse moving or the stop
	int node_number;
	///the number of passed nodes
	int counter;
	///current increment or decrement of counter
	int counter_incr;
	///speed of the platform
	int fixed_speed;
	///width of the current level
	int level_width;
	///height of the current level
	int level_height;
	///defines the shape of trajectory 'true' - closed 'false' - torn
	bool is_rouded;
	///defines the state of the platform 'true' - moves 'false' - doesn't move
	bool is_active;
	///defines whether platform stop itself 'true' - yes 'false' - not
	bool is_stop;
	///temprorary storage for platform coordinates
	b2Vec2 tmp;
	///causes platform to begin reverse moving
	void reverseMoving();
	///causes platform to begin moving to the next point
	void toNextPoint();
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
	Platform(int _level_width, int _level_height, b2Body* _body, Object* _object, std::vector<std::pair<double,double>> _traj_coord, int _fixed_speed, bool _is_rounded, int _node_number);
	///inherited from NonStaticObj class
	void update();
	virtual ~Platform(){};
};
