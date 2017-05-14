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
			win = new sf::RenderWindow(sf::VideoMode(800, 600), "GameTest");
			win->setFramerateLimit(60);
		}
		return win;
	}
};
