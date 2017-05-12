#pragma once

enum class Events 
{ 
	LoadLevel, 
	HeroMoveLeft,
	StopHeroMoveLeft,
	HeroMoveRight,
	StopHeroMoveRight,
	Jumping,
	StopHero,
	Move
};

enum class ViewEvents
{
	Update,
	LevelCreated
};

