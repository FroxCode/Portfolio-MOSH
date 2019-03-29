//Created By Jason Hannon
#include "ShaderEffect.h"

ShaderEffect::ShaderEffect()
{

}

ShaderEffect::ShaderEffect(sf::Vector2f pos, sf::Color color, float intensity)
{
	shape.setPosition(pos.x, pos.y);
	shape.setFillColor(sf::Color::Transparent);
	m_intensity = intensity;
	m_color = color;
}

ShaderEffect::~ShaderEffect() {}

void ShaderEffect::reload(sf::CircleShape aShape, sf::Color in_color, float intensity)
{
	shape = aShape;
	m_intensity = intensity;
	m_color = in_color;
	color = sf::Vector3f(m_color.r, m_color.g, m_color.b);
}

void ShaderEffect::draw(sf::RenderWindow & window)
{
	//window.draw(shape);
}
