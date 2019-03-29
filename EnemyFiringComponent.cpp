#include "EnemyFiringComponent.h"


EnemyFiringComponent::EnemyFiringComponent(){}
EnemyFiringComponent::~EnemyFiringComponent(){}

const double enemyPos = 0;

void EnemyFiringComponent::EnemyFiringPhysics(sf::Vector2i &enemyPosition, sf::Vector2i &playerPosition, sf::Vector2i &predictedPosition)
{

	double xDelta = enemyPosition.x - playerPosition.x;
	double yDelta = enemyPosition.y - playerPosition.y;
	double targetDistance = sqrt((xDelta*xDelta) + (yDelta*yDelta));

	// Prediction of shot.
	double impactTime = targetDistance / 1;
	xDelta += impactTime*enemyPosition.x;
	yDelta += impactTime*enemyPosition.y;

	predictedPosition.x = xDelta;
	predictedPosition.y = yDelta;

	// Gets new firing angle.
	double radian = atan(yDelta / xDelta);
	printf("new angle = %g\n", radian);

}