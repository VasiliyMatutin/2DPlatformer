#include "EndOfTheGame.h"

EndOfTheGame::EndOfTheGame()
{
	images.push_back("Images/MainMenu/black_screen.png");
	Object bs{ images.size() - 1, 0, 0, 0, 0, 0, 0, 0, true, 255 };
	unchangeable_objects.push_back(bs);

	images.push_back("Images/MainMenu/the_end.png");
	Object font{ images.size() - 1, 0, 0, 150, 200, 300, 500, 0, true, 255 };
	unchangeable_objects.push_back(font);

	images.push_back("Images/MainMenu/quit_button.png");
	Object new_button{ images.size() - 1, 0, 0, 300, 450, 75, 200, 0, true, 255 };
	unchangeable_objects.push_back(new_button);
	quit_button = &unchangeable_objects.back();
}

void EndOfTheGame::smthHappend(Events what_happened)
{
	switch (what_happened)
	{
	case Events::MouseClicked:
		if (isContains(MouseClickCoordinates::x, MouseClickCoordinates::y, quit_button))
		{
			re = ReturnEvents::OPENMENU;
			return;
		}
		break;
	}
}
