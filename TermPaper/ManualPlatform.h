#pragma once
#include "Platform.h"
#include "ManualSwitchObj.h"

class ManualPlatform : public Platform, public ManualSwitchObj
{
private:
	int node_number, counter, backup_counter=0;
public:
	ManualPlatform(int _level_width, int _level_height, b2Body* _body, Object* _object, std::vector<std::pair<double, double>> traj_coord, int _fixed_speed, bool _is_rounded, int _node_number);
	void update();
	void makeAction(Action);
	b2Body* getBody();
	Object* getObject();
	~ManualPlatform();
};
