#pragma once
#include"SFML\Graphics.hpp"

class WinSingleton
{
	static sf::RenderWindow *win;
	WinSingleton() = delete;
	~WinSingleton() = delete;
	WinSingleton(WinSingleton const&) = delete;
	WinSingleton& operator= (WinSingleton const&) = delete;
public:
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
	static void toFullScreen()
	{
		sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
		win->create(desktop, "GameTest",sf::Style::Fullscreen);
		win->setKeyRepeatEnabled(false); // To disable repeated KeyPressed events
		win->setFramerateLimit(60);
	}
	static void toWindow()
	{
		win->create(sf::VideoMode(800, 600), "GameTest");
		win->setKeyRepeatEnabled(false); // To disable repeated KeyPressed events
		win->setFramerateLimit(60);
	}
};
