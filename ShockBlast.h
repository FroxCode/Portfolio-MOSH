////////////////////////////////////////////////////////////
//
// Created by Emre
//
////////////////////////////////////////////////////////////
#ifndef _SHOCKBLAST_H
#define _SHOCKBLAST_H
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Bullet.h"

class ShockBlast : public Bullet{
public:
	////////////////////////////////////////////////////////////
	/// Default constructor
	///
	////////////////////////////////////////////////////////////
	ShockBlast();

	////////////////////////////////////////////////////////////
	/// Default constructor
	///
	////////////////////////////////////////////////////////////
	~ShockBlast();

	////////////////////////////////////////////////////////////
	/// Overloaded constructor
	///
	////////////////////////////////////////////////////////////
	ShockBlast(sf::Vector2f position, string const &texture);
private:

};
#endif