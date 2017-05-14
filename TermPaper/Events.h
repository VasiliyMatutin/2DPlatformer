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
	SwitchLever,
	Move
};

enum class ViewEvents
{
	Update,
	LevelCreated,
	BringZoomCloser,
	DistanseZoom,
};

