#ifndef _TOWER_H_
#define _TOWER_H_
#include <SFML\Graphics.hpp>
class Tower{
public:

	Tower();
	void update();
	void render(sf::RenderWindow &window);
	bool containsTower;
	sf::Vector2f position;
private:

};
#endif