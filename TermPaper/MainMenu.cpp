#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu()
{
	images.push_back("Images/MainMenu/font.png");
	Object font{ images.size() - 1, 0, 0, 0, 0, 0, 0, 0, true, 255 };
	unchangeable_objects.push_back(font);

	images.push_back("Images/MainMenu/play_button.png");
	Object new_button{ images.size() - 1, 0, 0, 300, 200, 138, 381, 0, true, 255 };
	unchangeable_objects.push_back(new_button);
	start_button = &unchangeable_objects.back();

	images.push_back("Images/MainMenu/exit_button.png");
	Object new_button2{ images.size() - 1, 0, 0, 300, 360, 138, 381, 0, true, 255 };
	unchangeable_objects.push_back(new_button2);
	exit_button = &unchangeable_objects.back();
}

void MainMenu::smthHappend(Events what_happened)
{
	switch (what_happened)
	{
	case Events::MouseClicked:
		if (isContains(MouseClickCoordinates::x, MouseClickCoordinates::y, start_button))
		{
			re = ReturnEvents::NEXTLEVEL;
			return;
		}
		if (isContains(MouseClickCoordinates::x, MouseClickCoordinates::y, exit_button))
		{
			re = ReturnEvents::CLOSE;
			return;
		}
		break;
	}
}
