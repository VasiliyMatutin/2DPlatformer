#include "Controller.h"

int main()
{
	Model model;
	Viewer viewer(&model);
	Controller controller(&model, &viewer);
	controller.observe();
	return 0;
}