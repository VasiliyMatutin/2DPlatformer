#include "LocalMenu.h"

LocalMenu::LocalMenu()
{
	images.push_back("Images/MainMenu/black_screen.png");
	Object bs{ images.size() - 1, 0, 0, 0, 0, 0, 0, 0, true, 200 };
	unchangeable_objects.push_back(bs);
	images.push_back("Images/MainMenu/pause.png");
	Object font{ images.size() - 1, 0, 0, 200, 50, 200, 400, 0, true, 255 };
	unchangeable_objects.push_back(font);

	images.push_back("Images/MainMenu/restart_button.png");
	Object new_button{ images.size() - 1, 0, 0, 300, 350, 75, 200, 0, true, 255 };
	unchangeable_objects.push_back(new_button);
	restart_button = &unchangeable_objects.back();

	images.push_back("Images/MainMenu/quit_button.png");
	Object new_button2{ images.size() - 1, 0, 0, 300, 450, 75, 200, 0, true, 255 };
	unchangeable_objects.push_back(new_button2);
	quit_button = &unchangeable_objects.back();

	images.push_back("Images/MainMenu/resume_button.png");
	Object new_button3{ images.size() - 1, 0, 0, 300, 250, 75, 200, 0, true, 255 };
	unchangeable_objects.push_back(new_button3);
	resume_button = &unchangeable_objects.back();
}

void LocalMenu::smthHappend(Events what_happened)
{
	switch (what_happened)
	{
	case Events::MOUSECLICKED:
		if (isContains(MouseClickCoordinates::x, MouseClickCoordinates::y, resume_button))
		{
			re = ReturnEvents::CLOSELOCALMENU;
			return;
		}
		if (isContains(MouseClickCoordinates::x, MouseClickCoordinates::y, restart_button))
		{
			re = ReturnEvents::RESTART;
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
