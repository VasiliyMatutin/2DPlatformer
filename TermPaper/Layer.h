/*! \file */

/**
\brief Determines a certain state of the model
\author Vasily
\version 1.0
\date June 2017

Class-layer with which works Model class
*/

#pragma once
#include <list>
#include <vector>
#include "Events.h"
#include"LevelBox.h"

class Layer
{
protected:
	///list of an layers objects which can't change during simulation process
	std::list<Object> unchangeable_objects;
	///list of an layers objects which can change during simulation process
	std::list<Object> changeable_objects;
	///list of an layers objects which represent layer UI
	std::list<Object*> UI_objects;
	///list of an layers text objects
	std::list<TextObject*> text_objects;
	///list of string names for all images dispalyes at this layer
	std::vector <std::string> images;
	///last event that happens at this layer
	ReturnEvents re;
	Layer();
public:
	virtual ~Layer() {};
	/*!
	\return list of an layers objects which can't change during simulation process
	*/
	std::list<Object> getUnchangeableObjects();
	/*!
	\return list of an layers objects which can change during simulation process
	*/
	std::list<Object> getChangeableObjects();
	/*!
	\return list of an layers objects which represent layer UI
	*/
	std::list<Object*> getUIObjects();
	/*!
	\return list of an layers text objects
	*/
	std::list<TextObject*> getTextObjects();
	/*!
	\brief provides opportunity to get layer width and height
	\param width pointer to the variable where width will be written
	\param height pointer to the variable where height will be written
	*/
	virtual void getLayerSize(double* width, double* height);
	/*!
	\brief provides opportunity to get layer center
	\param x pointer to the variable where x coordinate will be written
	\param y pointer to the variable where y coordinate will be written
	*/
	virtual void getLayerCenter(double* x, double* y);
	/*!
	\brief return the number of view entity on the level
	\return 'true' - two entities; 'false' - one entity
	*/
	virtual bool isDoubleView();
	/*!
	\brief Listener of player action

	Allow react to user action
	\param what_happened enum describing player action
	*/
	virtual void smthHappend(Events what_happened) = 0;
	///informs that level again active
	virtual void repause();
	///update layer state
	virtual void update();
	/*!
	\return list of string names for all images dispalyes at this layer
	*/
	virtual std::vector<std::string>& getImagesList();
	/*!
	\return pointer to the last event that happens at this layer
	*/
	virtual ReturnEvents* getRetEvent();
};