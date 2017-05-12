#pragma once
#include <vector>
#include "NonStaticObj.h"

class Platform : public NonStaticObj
{
private:
	std::vector<std::pair<int, int>> coord_set;
	int point_iter, incr;
	bool is_rouded;
	void toNextPoint(b2Vec2 tmp);
public:
	Platform(int _level_width, int _level_height, b2Body* _body, Object* _object, std::vector<std::pair<int,int>> traj_coord, int _fixed_speed, bool _is_rounded);
	void contactEvent(b2Contact * contact, bool is_begin);
	void update();
};
