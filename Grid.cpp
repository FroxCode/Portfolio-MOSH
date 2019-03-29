//Created by Dale Sinnott
#include "Grid.h"
Grid::Grid()
{

}
Grid::Grid(int width, int height, int offsetX, int offsetY) :
m_width(width),
m_height(height), 
m_offsetX(offsetX),
m_offsetY(offsetY)
{
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{//set tiles into grid
			std::shared_ptr<Tile> tempTile = std::make_shared<Tile>(Vector2f(x * 96 + m_offsetX, y * 96 + offsetY));
			tiles.push_back(tempTile);
		}
	}
	tiles.at(2)->canHaveWall = false;
}

Grid::~Grid()
{

}
void Grid::update(Vector2f &cursorPosition, int const PHASE)
{
	for (int i = 0; i < m_height * m_width; i++)
	{
		tiles.at(i)->update(cursorPosition, PHASE);
	}
}
void Grid::render(sf::RenderWindow &window)
{
	for (int i = 0; i < m_height * m_width; i++)
	{
		tiles.at(i)->render(window);
	}
}
void Grid::initialise(int width, int height, int offsetX, int offsetY)
{
	m_width = width;
	m_height = height;
	m_offsetX = offsetX;
	m_offsetY = offsetY;
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			std::shared_ptr<Tile> tempTile = std::make_shared<Tile>(Vector2f(y * 96 + m_offsetX, x * 96 + offsetY)); // x / y reversed to draw correctly
			tiles.push_back(tempTile);
		}
	}
	tiles.at(2)->canHaveWall = false; //make sure starting tile for enemy is always empty
} 