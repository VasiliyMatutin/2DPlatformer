#include "Bonus.h"

Bonus::Bonus(double modificator, double time, BonusType _bonus_type, Player* _current_player, Bonus** _active_bonus, b2Body* _body, Object* _object):
	bonus_modificator(modificator),
	time_interval(time),
	bonus_type(_bonus_type),
	current_player(_current_player),
	active_bonus(_active_bonus),
	body(_body),
	object(_object)
{
	body->SetUserData(this);
	b2Filter filter = body->GetFixtureList()->GetFilterData();
	filter.categoryBits = BONUSES;
	filter.maskBits = MASK_BONUSES;
	body->GetFixtureList()->SetFilterData(filter);
}

void Bonus::contactEvent(b2Contact *, bool)
{
	*active_bonus = this;
}

Object * Bonus::getObject()
{
	return object;
}

bool Bonus::activate(Object** _object)
{
	body->GetWorld()->DestroyBody(body);
	object->is_valid = false;
	current_player->activate_bonus(bonus_modificator, bonus_type);
	if (bonus_type != BonusType::HEALTH)
	{
		start = std::chrono::system_clock::now();
		(*_object)->number_in_image_list = object->number_in_image_list;
		interface_object = _object;
		(*interface_object)->is_valid = true;
		return true;
	}
	return false;
}

void Bonus::deactivate()
{
	(*interface_object)->is_valid = false;
	current_player->deactivate_bonus(bonus_modificator, bonus_type);
}

void Bonus::update()
{
	end = std::chrono::system_clock::now();
	duration = end - start;
	dts = std::chrono::duration_cast<std::chrono::seconds>(duration);
	time = dts.count();
	if (time > time_interval)
	{
		deactivate();
	}
}
