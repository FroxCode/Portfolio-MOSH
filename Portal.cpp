//Created by Emre Ozdemir
#include <Portal.h>
Portal::Portal(){}
Portal::~Portal(){}

Portal::Portal(sf::Vector2f position, string const &texture, int radius) :
Building(position, texture, radius)
{

}

void Portal::setPosition(Vector2f pos){

	m_sprite.setPosition(Vector2f(pos.x, pos.y));

}
void Portal::update()
{
	m_sprite.rotate(1.0f);
}