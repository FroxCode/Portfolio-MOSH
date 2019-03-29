//Created by Emre Ozdemir, Dale Sinnott
#include "Bullet.h"
#include <iostream>
#include <cmath>
Bullet::Bullet(){}
Bullet::~Bullet(){}

Bullet::Bullet(sf::Vector2f position, std::string const &texture) :
m_position(position)
{
	if (!m_texture.loadFromFile(texture))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	m_texture.setSmooth(true);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(16, 16);
	m_sprite.setPosition(m_position.x, m_position.y);
}
void Bullet::update(){
	
	if (is_alive)
	{ //if the bullet is alive
		m_position.x += direction.x * velocity * FPS; //move the bullet towards its target by its speed at a certain amount per frame
		m_position.y += direction.y * velocity * FPS;
		m_sprite.setPosition(m_position.x, m_position.y); //set the new position of the sprite
		
		if( m_position.x < 304 || m_position.x > 1072 || m_position.y < 120 || m_position.y > 600)
		{ //kill the bullet if it leaves the battlefield
			is_alive = false;
		}
	}
	else
	{ //set the bullet offscreen
		m_position.x = -100;
		m_position.y = -100;
		m_sprite.setPosition(m_position.x, m_position.y);
	}
}
void Bullet::render(RenderWindow &window)
{
	window.draw(m_sprite);

}

void Bullet::reset(Vector2f & target, Vector2f startPos)
{ //recreates the bullet
	is_alive = true; //make it alive
	startPoint = startPos; //new start position
	m_position = Vector2f(startPos.x, startPos.y); //set the new position of the sprite
	m_target = target; //assign the target
	distance = sqrt(((target.x - startPoint.x) * (target.x - startPoint.x)) + ((target.y - startPoint.y) * (target.y - startPoint.y))); //get distance from the points to eachother
	direction = Vector2f((target.x - startPoint.x) / distance, (target.y - startPoint.y) / distance); //get the direction vector
	m_position.x += direction.x * 48; //start the bullet already moved towards the target slightly
	m_position.y += direction.y * 48;
	m_sprite.setPosition(m_position.x, m_position.y);
}