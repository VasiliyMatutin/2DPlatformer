#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu():
	fs(0)
{
	images.push_back("Images/MainMenu/font.png");
	Object font{ images.size() - 1, 0, 0, 0, 0, 0, 0, 0, true, 255 };
	unchangeable_objects.push_back(font);

	introduction.text = "JUST 2D Platformer";
	introduction.text_size = 60;
	introduction.x = 510;
	introduction.y = 80;
	text_objects.push_back(&introduction);

	images.push_back("Images/MainMenu/play_button.png");
	Object new_button{ images.size() - 1, 0, 0, 300, 150, 138, 381, 0, true, 255 };
	unchangeable_objects.push_back(new_button);
	start_button = &unchangeable_objects.back();

	images.push_back("Images/MainMenu/exit_button.png");
	Object new_button2{ images.size() - 1, 0, 0, 300, 450, 138, 381, 0, true, 255 };
	unchangeable_objects.push_back(new_button2);
	exit_button = &unchangeable_objects.back();

	images.push_back("Images/MainMenu/fs_mode.png");
	Object new_button3{ images.size() - 1, 0, 0, 490, 370, 138, 381, 0, true, 255 };
	changeable_objects.push_back(new_button3);
	f_mode_button = &changeable_objects.back();

	images.push_back("Images/MainMenu/w_mode.png");
	Object new_button4{ images.size() - 1, 0, 0, 490, 370, 138, 381, 0, false, 255 };
	changeable_objects.push_back(new_button4);
	w_mode_button = &changeable_objects.back();
}

void MainMenu::smthHappend(Events what_happened)
{
	switch (what_happened)
	{
	case Events::MOUSECLICKED:
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
		if (isContainsC(MouseClickCoordinates::x, MouseClickCoordinates::y, f_mode_button))
		{
			f_mode_button->is_valid = !f_mode_button->is_valid;
			w_mode_button->is_valid = !w_mode_button->is_valid;
			fs = !fs;
			if (fs)
			{
				re = ReturnEvents::FULLSCREEN;
			}
			else
			{
				re = ReturnEvents::WINDOWED;
			}
			return;
		}
		break;
	}
}

bool MainMenu::isContainsC(double x, double y, Object * button)
{
	if (x > button->x - button->width / 2 &&
		x < button->x + button->width / 2 &&
		y > button->y - button->height / 2  &&
		y < button->y + button->height / 2)
	{
		return true;
	}
	return false;
}
