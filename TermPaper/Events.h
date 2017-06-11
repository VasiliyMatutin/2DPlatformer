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
	EscButton,
	EnterButton,
	MouseClicked
};

enum class ViewEvents
{
	ADDLAYER,
	DELETELAYER,
	DELETEALLLAYERS,
	BRINGZOOMCLOSER,
	DISTANCEZOOM,
	WINRESIZE,
};

enum class ReturnEvents
{
	NEXTLEVEL,
	CLOSE,
	RESTART,
	GAMEOVER,
	WIN,
	OPENMENU,
	OPENLOCALMENU,
	CLOSELOCALMENU,
	DEFAULT
};

enum class ModelReaction
{
	ADD,
	DELETE,
	CLEARALLANDADD,
	CLOSE,
	NOTHING
};

struct MouseClickCoordinates
{
	static double x;
	static double y;
};

struct PositionRelativelyScreen
{
	static double x;
	static double y;
};

static double X_WIN_SIZE = 800;
static double Y_WIN_SIZE = 600;