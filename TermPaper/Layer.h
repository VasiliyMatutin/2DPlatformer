#pragma once
#include <list>
#include <vector>
#include "Events.h"
#include"LevelBox.h"

enum class ReturnEvents
{
	NextLevel,
	OpenMenu,
	CloseLayer,
	DEFAULT
};

class Layer
{
protected:
	std::list<Object> unchangeable_objects;
	std::list<Object> changeable_objects;
	std::list<Object*> UI_objects;
	std::list<TextObject*> text_objects;
public:
	virtual ~Layer() {};
	std::list<Object> getUnchangeableObjects();
	std::list<Object> getChangeableObjects();
	std::list<Object*> getUIObjects();
	std::list<TextObject*> getTextObjects();
	virtual void getLayerCenter(double* x, double* y);
	virtual bool isDoubleView();
	virtual void smthHappend(Events what_happened) = 0;
	virtual void update();
	virtual std::vector<std::string>& getImagesList() = 0;
	virtual ReturnEvents getRetEvent() = 0;
};