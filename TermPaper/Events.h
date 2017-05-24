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
	PickUp,
	ChangeHero,
	MouseClicked,
	Move
};

enum class ViewEvents
{
	Update,
	LevelCreated,
	BringZoomCloser,
	DistanseZoom,
};

struct MouseClickCoordinates
{
	static double x;
	static double y;
};