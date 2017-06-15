/*! \file */

#pragma once

///sfml events trasfer into apllication command
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

///Controller commands to Viewer
enum class ViewEvents
{
	ADDLAYER,
	DELETELAYER,
	DELETEALLLAYERS,
	BRINGZOOMCLOSER,
	DISTANCEZOOM,
	WINRESIZE,
};

///Layer events
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

///information about last state that Model return to Controller
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

/**
\brief last registered mouse click coordinates
\author Vasily
\version 1.0
\date June 2017
*/
struct MouseClickCoordinates
{
	/// x coordinates
	static double x;
	/// y coordinates
	static double y;
};

/**
\brief hero position relatively screen, not level
\author Vasily
\version 1.0
\date June 2017
*/
struct PositionRelativelyScreen
{
	/// x coordinates
	static double x;
	/// y coordinates
	static double y;
};

///default windows size on x coordinate
static double X_WIN_SIZE = 800;
///default windows size on y coordinate
static double Y_WIN_SIZE = 600;