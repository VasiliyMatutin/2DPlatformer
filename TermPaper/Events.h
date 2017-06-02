#pragma once

enum class Events 
{ 
	LeftButton,
	LeftButtonReleased,
	RightButton,
	RightButtonReleased,
	UpButton,
	UpButtonReleased,
	IButton,
	PButton,
	CButton,
	MouseClicked
};

enum class ViewEvents
{
	AddLayer,
	DeleteLayer,
	BringZoomCloser,
	DistanseZoom,
};

struct MouseClickCoordinates
{
	static double x;
	static double y;
};