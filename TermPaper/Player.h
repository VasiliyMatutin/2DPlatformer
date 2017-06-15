/*! \file */

/**
\brief Parent class for DexterousPlayer and StrongPlayer classes
\author Vasily
\version 1.0
\date June 2017

Contain base information about characret besides its type
*/

#pragma once
#include "NonStaticObj.h"
#include "PlayerUI.h"
#include "Events.h"
#include "Bonus.h"

class Player : public NonStaticObj
{
protected:
	///current row in image tileset for this hero
	int img_row;
	///row in image tileset for left moving
	int left_row;
	///row in image tileset for right moving
	int right_row;
	///max column number in image tileset 
	int max_frame;
	///default speed of the character
	int fixed_speed;
	///width of the current level
	int level_width;
	///height of the current level
	int level_height;
	///the maximum level of health reserve for this caracter 
	int max_health;
	///current level of health reserve for this caracter 
	int health;
	///Define character position 'false' - in air; 'true' - on ground
	int on_ground;
	///Define characters animation 'false' - non-animated; 'true' - animated
	bool is_animated;
	///Define was stop or not 'false' - wasn't; 'true' - was
	bool is_stop;
	///current column number in image tileset 
	double current_frame;
	///speed of hero animation
	double current_frequency;
	///current speed of the hero
	double x_speed;
	///delta-speed for maintaining constant speed in physics world
	double desired_vel;
	///strenght of the heros jump
	double jump_strenght;
	///pointer to the variable, which contains reply of the current level during last iteration (see Layer class)
	ReturnEvents* re;
	///Pointer to the bonus which will be activated at the next update iteration
	Bonus* activate_this_bonus;
	///Pointer to the array of player ui bonus cell
	Bonus* active_bonus[3];
	///contains UI information for this player
	PlayerUI playerUI;
	/*!
	\brief Defined constructor for this class
	\param _level_width the width in pixels of this level
	\param _level_height the height in pixels of this level
	\param _body pointer to the box2d body assigned to this character
	\param _object pointer to the Object class assigned to this character
	\param _health the maximum level of health reserve for this caracter
	\param _re pointer to the variable which contains reply of the current level during last iteration (see Layer class)
	*/
	Player(int _level_width, int _level_height, b2Body * _body, Object * _object, int _health, ReturnEvents* _re);
	///Update UI information for this hero
	void updateUI();
public:
	/*!
	\brief Apllies the bonus effect to the hero
	\param modificator bonuse strength of impact
	\param bonus_type bonuse type (see enum BonusType)
	*/
	void activate_bonus(double modificator, BonusType bonus_type);
	/*!
	\brief Terminates the action of the bonus effect to the hero
	\param modificator bonuse strength of impact
	\param bonus_type bonuse type (see enum BonusType)
	*/
	void deactivate_bonus(double modificator, BonusType bonus_type);
	///causes the hero to jump
	void jump();
	///causes the hero to increase left-moving speed
	void moveLeft();
	///causes the hero to increase right-moving speed
	void moveRight();
	///causes the hero to decrease right-moving speed
	void stopRight();
	///causes the hero to decrease left-moving speed
	void stopLeft();
	///causes the hero to stop completely
	void justStop();
	/*!
	\return current hero speed
	*/
	double getVel();
	/*!
	\param des_vel set desired speed of the hero
	*/
	void setVel(double des_vel);
	///Notifies about the begginning of the hero's contact with the ground
	void beginContactWithGround();
	///Notifies about the end of the hero's contact with the ground
	void endContactWithGround();
	/*!
	\return pointer to the bonus which will be activated at the next update iteration
	*/
	Bonus** getActivationBonus();
	/*!
	Set in input arguments current hero coordinates
	\param x pointer to the variable where set x coordinate
	\param y pointer to the variable where set y coordinate
	*/
	void returnCoordinates(double* x, double* y);
	/*!
	\return pointer to the PlayerUI class
	*/
	PlayerUI* returnUI();
	///inhereted from NonStaticObj class
	bool destroy();
	///inherited from NonStaticObj class
	void update();
};
