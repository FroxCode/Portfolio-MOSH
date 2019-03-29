////////////////////////////////////////////////////////////
//
// Created by Connor
// Worked on Dale and Emre
//
////////////////////////////////////////////////////////////
#ifndef _BUILDING_H_
#define _BUILDING_H_
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML\Graphics.hpp>
#include <memory>


using namespace std;
using namespace sf;
class Building{

public:
	////////////////////////////////////////////////////////////
	/// Default constructor
	///
	////////////////////////////////////////////////////////////
	Building();

	////////////////////////////////////////////////////////////
	/// Default destructor
	///
	////////////////////////////////////////////////////////////
	~Building();

	////////////////////////////////////////////////////////////
	/// Overloaded constructor
	///
	////////////////////////////////////////////////////////////
	Building(sf::Vector2f position, std::string const &texture, int radius);

	////////////////////////////////////////////////////////////
	/// Draws the object
	///
	////////////////////////////////////////////////////////////
	void render(RenderWindow &window);

	////////////////////////////////////////////////////////////
	/// Sets the angle to which the tower rotates 
	/// to an enemy position
	////////////////////////////////////////////////////////////
	void setTowerRotationAngle(sf::Vector2f &pos);

	////////////////////////////////////////////////////////////
	/// Rotates the object
	///
	////////////////////////////////////////////////////////////
	bool rotateTower();

	int const MAX_BULLETS = 10;
	bool aligned;
	Vector2f m_position;
	bool is_alive = false;
	Texture m_texture;
	Sprite m_sprite;
	CircleShape m_circle;

};
#endif