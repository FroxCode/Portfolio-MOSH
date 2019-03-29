//Created by Emre Ozdemir
#include "ShockBlast.h"
ShockBlast::ShockBlast(){}
ShockBlast::~ShockBlast(){}

ShockBlast::ShockBlast(sf::Vector2f position, string const &texture) :
Bullet(position, texture)
{
	damage = 20;
	type = 2;
}
