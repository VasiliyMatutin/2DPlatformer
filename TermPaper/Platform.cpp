#include "Platform.h"

Platform::Platform(int _level_width, int _level_height, b2Body * _body, Object * _object, std::vector<std::pair<int, int>> traj_coord, int _fixed_speed, bool _is_rounded) : NonStaticObj(_level_width, _level_height, _body, _object, _fixed_speed),
	coord_set(traj_coord),
	point_iter(0),
	incr(1),
	is_rouded(_is_rounded)
{
	body->SetTransform(b2Vec2(coord_set[0].first, coord_set[0].second), 0);
	body->GetFixtureList()->SetFriction(0.0f);
	body->SetUserData(this);
}

void Platform::contactEvent(b2Contact * contact, bool is_begin)
{
	b2Manifold* contact_information = contact->GetManifold();
	b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);
	if (is_begin && contact_information->localNormal.y != 0 && worldManifold.points[0].y - object->y > 0)
	{
		b2Vec2 tmp = body->GetPosition();
		incr = -incr;
		toNextPoint(tmp);
		return;
	}
}

void Platform::update()
{
	b2Vec2 tmp = body->GetPosition();
	object->x = tmp.x;
	object->y = tmp.y;
	if (abs(tmp.x - coord_set[point_iter].first) < 0.1 && abs(tmp.y - coord_set[point_iter].second) < 0.1)
	{
		if (point_iter == coord_set.size() - 1)
		{
			if (is_rouded)
			{
				point_iter = 0;
			}
			else
			{
				incr = -incr;
			}
		}
		else if (point_iter == 0)
		{
			incr = 1;
		}
		toNextPoint(tmp);
		//body->SetTransform(b2Vec2(coord_set[0].first, coord_set[0].second), 0);
	}
	else if (object->x + object->width / 2 > level_width - 0.001 || object->x - object->width / 2 < 0.001 || object->y + object->height  / 2 > level_height - 0.001 || object->y - object->height / 2 < 0.001) //check of collisions with level boundaries
	{
		incr = -incr;
		is_rouded = false;
		toNextPoint(tmp);
	}
}

void Platform::toNextPoint(b2Vec2 tmp)
{
	point_iter += incr;
	b2Vec2 direction(coord_set[point_iter].first - tmp.x, coord_set[point_iter].second - tmp.y);
	direction.Normalize();
	body->SetLinearVelocity(b2Vec2(fixed_speed*direction.x, fixed_speed*direction.y));
}
