#include "Bonus.h"
#include "Player.h"

Bonus::Bonus(double modificator, double time, BonusType _bonus_type, Player** _current_player, b2Body* _body, Object* _object, std::chrono::duration<double>* _duration):
	bonus_modificator(modificator),
	time_interval(time),
	bonus_type(_bonus_type),
	current_player(_current_player),
	body(_body),
	object(_object),
	duration(_duration)
{
	body->SetUserData(this);
	b2Filter filter = body->GetFixtureList()->GetFilterData();
	filter.categoryBits = BONUSES;
	filter.maskBits = MASK_BONUSES;
	body->GetFixtureList()->SetFilterData(filter);
}

void Bonus::contactEvent(b2Contact *, bool)
{
	*((*current_player)->getActivationBonus()) = this;
}

Object * Bonus::getObject()
{
	return object;
}

bool Bonus::activate(Object* _object)
{
	body->GetWorld()->DestroyBody(body);
	object->is_valid = false;
	(*current_player)->activate_bonus(bonus_modificator, bonus_type);
	if (bonus_type != BonusType::HEALTH)
	{
		iam_activate_this_player = *current_player;
		start = *duration;
		_object->number_in_image_list = object->number_in_image_list;
		object = _object;
		object->is_valid = true;
		return true;
	}
	return false;
}

void Bonus::deactivate()
{
	object->is_valid = false;
	iam_activate_this_player->deactivate_bonus(bonus_modificator, bonus_type);
}

void Bonus::update()
{
	dts = std::chrono::duration_cast<std::chrono::seconds>(*duration-start);
	time = dts.count();
	if (time > time_interval)
	{
		deactivate();
	}
}
