
////////////////////////////////////////////////////////////
//
// Created by Dale
//
////////////////////////////////////////////////////////////
#ifndef _TILE_H_
#define _TILE_H_
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML\Graphics.hpp>
#include <memory>
#include "Wall.h"
using namespace sf;
class Tile{
public:
	////////////////////////////////////////////////////////////
	/// constructor
	///
	////////////////////////////////////////////////////////////
	explicit Tile(sf::Vector2f position, int size = 96);

	////////////////////////////////////////////////////////////
	/// constructor
	///
	////////////////////////////////////////////////////////////
	Tile(const Tile&) = delete;

	////////////////////////////////////////////////////////////
	/// overloaded  operator
	///
	////////////////////////////////////////////////////////////
	Tile& operator =(const Tile&) = delete;

	////////////////////////////////////////////////////////////
	/// Default constructor
	///
	////////////////////////////////////////////////////////////
	~Tile();

	////////////////////////////////////////////////////////////
	/// update sthe tiles
	///
	////////////////////////////////////////////////////////////
	void update(sf::Vector2f &cursorPosition, int const PHASE);

	////////////////////////////////////////////////////////////
	/// renders the tiles
	///
	////////////////////////////////////////////////////////////
	void render(sf::RenderWindow &window);
	bool containsWall = false;
	bool isHighlighted = false;
	bool canHaveWall;
	std::unique_ptr<Wall> m_wall;
	sf::Vector2f m_position;
	float m_width;
	float m_height;
	sf::IntRect bounds;
	sf::RectangleShape m_rect;
private:

};
#endif