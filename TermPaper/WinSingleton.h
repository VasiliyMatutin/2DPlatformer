/*! \file */

/**
\brief Application window
\author Vasily
\version 1.0
\date June 2017
*/

#pragma once
#include"SFML\Graphics.hpp"

class WinSingleton
{
	///sfml window
	static sf::RenderWindow *win;
	WinSingleton() = delete;
	~WinSingleton() = delete;
	WinSingleton(WinSingleton const&) = delete;
	WinSingleton& operator= (WinSingleton const&) = delete;
public:
	/*!
	\brief create new or return unique application window
	\return application window
	*/
	static sf::RenderWindow* getInstance()
	{
		if (!win)
		{
			win = new sf::RenderWindow(sf::VideoMode(800,600), "GameTest");
			win->setKeyRepeatEnabled(false); // To disable repeated KeyPressed events
			win->setFramerateLimit(60);
		}
		return win;
	}
	///change window mode to fullscreen
	static void toFullScreen()
	{
		sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
		win->create(desktop, "GameTest",sf::Style::Fullscreen);
		win->setKeyRepeatEnabled(false); // To disable repeated KeyPressed events
		win->setFramerateLimit(60);
	}
	///change window mode to 800*600
	static void toWindow()
	{
		win->create(sf::VideoMode(800, 600), "GameTest");
		win->setKeyRepeatEnabled(false); // To disable repeated KeyPressed events
		win->setFramerateLimit(60);
	}
};
