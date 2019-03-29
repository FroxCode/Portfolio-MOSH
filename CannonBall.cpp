//Created by Emre Ozdemir
#include "CannonBall.h"
CannonBall::CannonBall(){}
CannonBall::~CannonBall(){}

CannonBall::CannonBall(sf::Vector2f position, string const &texture) :
Bullet(position, texture)
{//custom damages
	damage = 35;
	type = 1;
}