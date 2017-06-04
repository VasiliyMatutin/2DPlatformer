#include "GameOver.h"

GameOver::GameOver(bool is_bad) :
	is_bad(is_bad)
{
	images.push_back("Images/MainMenu/black_screen.png");
	Object bs{ images.size() - 1, 0, 0, 0, 0, 0, 0, 0, true, 200 };
	unchangeable_objects.push_back(bs);
	if (is_bad)
	{
		images.push_back("Images/MainMenu/game_over.png");
		Object font{ images.size() - 1, 0, 0, 150, 100, 300, 500, 0, true, 255 };
		unchangeable_objects.push_back(font);

		images.push_back("Images/MainMenu/restart_button.png");
		Object new_button{ images.size() - 1, 0, 0, 150, 450, 75, 200, 0, true, 255 };
		unchangeable_objects.push_back(new_button);
		restart_button = &unchangeable_objects.back();
	}
	else
	{
		images.push_back("Images/MainMenu/win.png");
		Object font{ images.size() - 1, 0, 0, 150, 100, 300, 500, 0, true, 255 };
		unchangeable_objects.push_back(font);

		images.push_back("Images/MainMenu/next_button.png");
		Object new_button{ images.size() - 1, 0, 0, 150, 450, 75, 200, 0, true, 255 };
		unchangeable_objects.push_back(new_button);
		restart_button = &unchangeable_objects.back();
	}
	images.push_back("Images/MainMenu/quit_button.png");
	Object new_button2{ images.size() - 1, 0, 0, 450, 450, 75, 200, 0, true, 255 };
	unchangeable_objects.push_back(new_button2);
	quit_button = &unchangeable_objects.back();
}

void GameOver::smthHappend(Events what_happened)
{
	switch (what_happened)
	{
	case Events::MouseClicked:
		if (isContains(MouseClickCoordinates::x, MouseClickCoordinates::y, restart_button))
		{
			if (is_bad)
			{
				re = ReturnEvents::RESTART;
			}
			else
			{
				re = ReturnEvents::NEXTLEVEL;
			}
			return;
		}
		if (isContains(MouseClickCoordinates::x, MouseClickCoordinates::y, quit_button))
		{
			re = ReturnEvents::OPENMENU;
			return;
		}
		break;
	}
}
