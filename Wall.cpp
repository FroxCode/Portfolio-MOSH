//Created by Emre Ozdemir
#include <Wall.h>
Wall::Wall(){}
Wall::~Wall(){}

Wall::Wall(sf::Vector2f position, string const &texture, int radius) :
Building(position, texture, radius)
{

}
void Wall::setPosition(Vector2f pos){

	m_sprite.setPosition(pos);

}
void Wall::render(sf::RenderWindow &window)
{

	window.draw(m_sprite);
	if (m_turret != nullptr)
	{
		m_turret->update();
		m_turret->render(window);
	}
	else if (m_tesla != nullptr)
	{
		m_tesla->update();
		m_tesla->render(window);
	}

}
