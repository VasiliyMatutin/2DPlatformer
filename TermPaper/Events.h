#pragma once

enum class Events 
{ 
	LEFTBUTTON,
	LEFTBUTTONRELEASED,
	RIGHTBUTTON,
	RIGHTBUTTONRELEASED,
	UPBUTTON,
	UPBUTTONRELEASED,
	IBUTTON,
	PBUTTON,
	CBUTTON,
	ESCBUTTON,
	ENTERBUTTON,
	MOUSECLICKED
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
	DEFAULT,
	FULLSCREEN,
	WINDOWED
};

enum class ModelReaction
{
	ADD,
	REMOVE,
	CLEARALLANDADD,
	CLOSE,
	NOTHING,
	FULLSCREEN,
	WINDOWED
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