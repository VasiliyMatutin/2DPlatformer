#pragma once
#include "AuxiliaryLayer.h"

class ErrorWindow : public AuxiliaryLayer
{
private:
	TextObject introduction;
	TextObject error_msg;
	TextObject conclusion;
	Object* ok_button;
public:
	ErrorWindow();
	void setErrorMsg(std::string error_msg);
	void smthHappend(Events what_happened);
};
