//Created by Connor Maguire, Dale Sinnott, Emre Ozdemir
#include "Building.h"
Building::Building(){}
Building::~Building(){}

// Constant for PI
const double PI = 4.0 * atan(1.0);
// Rotate to point for a tower, bool indicates alignment with point.
std::pair<int, bool> rotateToPoint(0, true);

Building::Building(sf::Vector2f position, std::string const &texture, int radius = 0) :
m_position(position)
{

	if (!m_texture.loadFromFile(texture))
	{ //load texture
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	m_texture.setSmooth(true); //smooth the pixelated image
	m_sprite.setOrigin(sf::Vector2f(48, 48)); //center the origin
	m_sprite.setTexture(m_texture); //assign the sprites texture
	m_sprite.setPosition(Vector2f(m_position.x, m_position.y)); //set position of the sprite
	m_circle.setPosition(Vector2f(m_position.x, m_position.y)); //building's range
	m_circle.setFillColor(Color(255, 255, 255, 30));
	m_circle.setOutlineThickness(4);
	m_circle.setOutlineColor(Color(255, 255, 255, 80));
	m_circle.setRadius(radius * 96); //range of tiles
}
void Building::render(RenderWindow &window)
{ //draw
	window.draw(m_sprite);
}

void Building::setTowerRotationAngle(sf::Vector2f &position)
{ //trig to calculate angle of rotation to point
	sf::Vector2f pos(position.y - m_sprite.getPosition().y, position.x - m_sprite.getPosition().x);

	float theta_deg = atan2(-1 * pos.y, pos.x) / PI * 180 + 180;
	rotateToPoint.first = std::round(theta_deg);
	rotateToPoint.second = false;
}
bool Building::rotateTower()
{
	bool aligned = true;
	int degrees = m_sprite.getRotation();
	if (degrees + 3 <= rotateToPoint.first || degrees - 3 >= rotateToPoint.first)
	{ //check if the turret is aligned +/-3 degrees of target
		aligned = false;
		int rotation = rotateToPoint.first - degrees;
		int signOfRotation = std::copysign(1.0f, rotation); // get the sign of the number rotation (+ or -)
		int rotationSpeedDegrees = 3;
		// If close to desired heading, slow down rotation speed to 1 degree increments.
		if (std::abs(rotation) <= rotationSpeedDegrees)
		{
			rotationSpeedDegrees = 1;
		}
		if (std::abs(rotation) < 180)
		{
			m_sprite.rotate(signOfRotation * rotationSpeedDegrees);
		}
		else // degrees >= 180
		{
			m_sprite.rotate(-1.0f * signOfRotation * rotationSpeedDegrees);
		}
	}
	
	return aligned;

}