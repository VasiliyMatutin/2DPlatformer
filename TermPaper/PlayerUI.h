/*! \file */

/**
\brief Contains the necessary-for-display information about the hero
\author Vasily
\version 1.0
\date June 2017
*/

#pragma once
#include "LevelBox.h"

class PlayerUI
{
private:
	///player name
	TextObject player_name;
	///player type (strong or dexterous)
	TextObject player_type;
	///array of bonus cell
	Object active_bonuses[3];
	///health bar
	Object health{ 0, 0, 0, 28, 52, 10, 99, 0, true, 255 };
	///Prepares array of bonus cell
	void createBonusUI();
public:
	///default constructor
	PlayerUI();
	/*!
	\return TextObject with player name
	*/
	TextObject* getPlayerName();
	/*!
	\return TextObject with player type
	*/
	TextObject* getPlayerType();
	/*!
	\brief set level of health bar
	\param i level of hero health
	*/
	void setHealthLineImg(int i);
	/*!
	\param name player name
	*/
	void setPlayerName(std::string name);
	/*!
	\param type player type
	*/
	void setPlayerType(std::string type);
	/*!
	\brief return bonus Object from defined ui cell
	\param number cell-number
	\return bonus Object in this cell
	*/
	Object* getActiveBonusesPtr(int number);
	/*!
	\return health bar Object
	*/
	Object* getHealthPtr();
};
