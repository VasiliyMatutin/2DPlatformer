#include <windows.h>  
#include <tchar.h> 
#include "Controller.h"

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
	Model model;
	Viewer viewer(&model);
	Controller controller(&model, &viewer);
	controller.observe();
	return 0;
}