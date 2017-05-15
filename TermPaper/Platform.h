#pragma once
#include <vector>
#include "NonStaticObj.h"

class Platform : public NonStaticObj
{
protected:
	std::vector<std::pair<double, double>> coord_set;
	int point_iter, incr, node_number, counter, counter_incr, fixed_speed;
	bool is_rouded, is_active;
	b2Vec2 tmp;
	void reverseMoving();
	void toNextPoint();
public:
	Platform(int _level_width, int _level_height, b2Body* _body, Object* _object, std::vector<std::pair<double,double>> traj_coord, int _fixed_speed, bool _is_rounded, int _node_number);
	void contactEvent(b2Contact * contact, bool is_begin);
	void update();
	virtual ~Platform();
};
