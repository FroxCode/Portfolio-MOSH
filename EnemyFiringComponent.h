#ifndef _ENEMYFIRINGCOMPONENT_H
#define _ENEMYFIRINGCOMPONENT_H
#include <SFML\Graphics.hpp>
#include <iostream>
#include <queue>
#include <string>
#include <math.h>
#include <memory>

using namespace std;
using namespace sf;

class EnemyFiringComponent{
public:
	EnemyFiringComponent();
	~EnemyFiringComponent();
	void EnemyFiringPhysics(sf::Vector2i &enemyPosition, sf::Vector2i &playerPosition, sf::Vector2i &predictedPosition);


};



#endif