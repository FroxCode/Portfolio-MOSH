//Created by Emre Ozdemir
#include "Rocket.h"
Rocket::Rocket(){}
Rocket::~Rocket(){}

Rocket::Rocket(sf::Vector2f position, string const &texture) :
Bullet(position, texture)
{
	damage = 150;
	type = 3;
}
void Rocket::update(){

	if (is_alive)
	{
		velocity.x = velocity.x - airResistance;
		m_position.x += direction.x * velocity.x * FPS;
		m_position.y += direction.y * velocity.y * FPS;
		m_sprite.setPosition(m_position.x, m_position.y);

		if (m_position.x < 304 || m_position.x > 1072 || m_position.y < 120 || m_position.y > 600)
		{
			is_alive = false;
		}
	}
	else
	{
		m_position.x = -100;
		m_position.y = -100;
		velocity = Vector2f(400, 400);
		m_sprite.setPosition(m_position.x, m_position.y);
	}
}