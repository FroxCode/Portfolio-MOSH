//Created by Dale Sinnott
#include "Tile.h"
Tile::Tile(sf::Vector2f const position, int const size) :
bounds(Vector2i(position), sf::Vector2i(size,size)),
m_position(position),
m_wall(nullptr)
{
	
	m_rect.setSize(sf::Vector2f(size, size));
	m_rect.setOutlineColor(Color::White);
	m_rect.setOutlineThickness(0);
	m_rect.setPosition(Vector2f(position.x, position.y));
}
Tile::~Tile()
{

}
void Tile::update(sf::Vector2f &cursorPosition, int const PHASE)
{
	m_rect.setFillColor(Color::Transparent);
	if (canHaveWall)
	{
		if (bounds.contains(Vector2i(cursorPosition)))
		{
			isHighlighted = true;
		}
		else
		{
			isHighlighted = false;
		}
	}
}
void Tile::render(sf::RenderWindow &window)
{
		window.draw(m_rect);
		if (m_wall != nullptr)
		{
			m_wall->render(window);
		}
	
}