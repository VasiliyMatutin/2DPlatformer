#include "Controller.h"

int main()
{
	Model model;
	Viewer viewer(&model);
	Controller controller(&viewer, &model);
	controller.observe();
	return 0;
}