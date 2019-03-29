////////////////////////////////////////////////////////////
//
// Created by Jason
//
////////////////////////////////////////////////////////////
#ifndef _SHADEREFFECT_H
#define _SHADEREFFECT_H
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFML/Graphics.hpp"
#include <random>
#include <chrono>

class ShaderEffect{
public:
	////////////////////////////////////////////////////////////
	/// Default constructor
	///
	////////////////////////////////////////////////////////////
	ShaderEffect();

	////////////////////////////////////////////////////////////
	/// Overloaded constructor
	///
	////////////////////////////////////////////////////////////
	ShaderEffect(sf::Vector2f pos, sf::Color color, float intensity);

	////////////////////////////////////////////////////////////
	/// destructor
	///
	////////////////////////////////////////////////////////////
	virtual ~ShaderEffect();

	////////////////////////////////////////////////////////////
	/// Draws the shader effect
	///
	////////////////////////////////////////////////////////////
	void draw(sf::RenderWindow &window);

	////////////////////////////////////////////////////////////
	/// reloads the shader
	///
	////////////////////////////////////////////////////////////
	void reload(sf::CircleShape aShape, sf::Color in_color, float intensity);

	sf::Vector2f getPosition() const 
	{
		return shape.getPosition();
	}
	sf::Vector3f getColor() const 
	{
		return color;
	}
	float x() const 
	{
		return shape.getPosition().x;
	}
	float y() const 
	{
		return shape.getPosition().y;
	}
	float left() const 
	{
		return x() - shape.getRadius() / 2.0f;
	}
	float right() const 
	{
		return x() + shape.getRadius() / 2.0f;
	}
	float top() const 
	{
		return y() - shape.getRadius() / 2.0f;
	}
	float bottom() const 
	{
		return y() + shape.getRadius() / 2.0f;
	}
	float getIntensity() //const
	{
		return m_intensity;
	}

private:

	sf::CircleShape shape;
	sf::Texture m_texture;
	sf::Vector3f color;
	sf::Color m_color;
	float m_intensity;
};

#endif