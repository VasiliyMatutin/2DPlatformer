#include "ErrorWindow.h"

ErrorWindow::ErrorWindow()
{
	images.push_back("Images/MainMenu/font.png");
	Object bs{ images.size() - 1, 0, 0, 0, 0, 0, 0, 0, true, 250 };
	unchangeable_objects.push_back(bs);

	images.push_back("Images/MainMenu/ok_button.png");
	Object new_button{ images.size() - 1, 0, 0, 300, 360, 138, 381, 0, true, 255 };
	unchangeable_objects.push_back(new_button);
	ok_button = &unchangeable_objects.back();

	introduction.text = "Unfortunately it's impossible \n \t\t to load this level";
	introduction.text_size = 45;
	introduction.x = 510;
	introduction.y = 100;
	text_objects.push_back(&introduction);

	error_msg.text_size = 24;
	error_msg.x = 500;
	error_msg.y = 200;
	text_objects.push_back(&error_msg);

	conclusion.text_size = 36;
	conclusion.text = "Please contact level designer";
	conclusion.x = 500;
	conclusion.y = 300;
	text_objects.push_back(&conclusion);
}

void ErrorWindow::setErrorMsg(std::string error_msg)
{
	this->error_msg.text = "Error: " + error_msg;
}

void ErrorWindow::smthHappend(Events what_happened)
{
	switch (what_happened)
	{
	case Events::MOUSECLICKED:
		if (isContains(MouseClickCoordinates::x, MouseClickCoordinates::y, ok_button))
		{
			re = ReturnEvents::OPENMENU;
			return;
		}
		break;
	}
}
