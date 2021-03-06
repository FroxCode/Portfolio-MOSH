
////////////////////////////////////////////////////////////
//
// Created by Connor
// Worked on by Dale
//
////////////////////////////////////////////////////////////
#ifndef _TURRET_H_
#define _TURRET_H_
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Building.h>
#include "CannonBall.h"
#include "CheckShaders.h"
#include "SoundManager.h"
#include "Enemy.h"
#include "Bullet.h"
class Turret : public Building
{
public:
	////////////////////////////////////////////////////////////
	/// Default constructor
	///
	////////////////////////////////////////////////////////////
	Turret();

	////////////////////////////////////////////////////////////
	/// Default constructor
	///
	////////////////////////////////////////////////////////////
	~Turret();

	////////////////////////////////////////////////////////////
	/// Overloaded constructor
	///
	////////////////////////////////////////////////////////////
	Turret(sf::Vector2f position, string const &texture, int radius);

	////////////////////////////////////////////////////////////
	/// Targets the closest enemy
	///
	////////////////////////////////////////////////////////////
	void targetEnemy(shared_ptr<Enemy> enemy);

	////////////////////////////////////////////////////////////
	/// sets the turrets position
	///
	////////////////////////////////////////////////////////////
	void setPosition(Vector2f pos);

	////////////////////////////////////////////////////////////
	/// default method that shoots projectiles
	///
	////////////////////////////////////////////////////////////
	void fire();

	////////////////////////////////////////////////////////////
	/// updates the turret
	///
	////////////////////////////////////////////////////////////
	void update();

	////////////////////////////////////////////////////////////
	/// Renders the turret
	///
	////////////////////////////////////////////////////////////
	void render(RenderWindow &window);
	bool is_Selected;

	////////////////////////////////////////////////////////////
	/// Overloader method that fires projectiles
	///
	////////////////////////////////////////////////////////////
	void fire(Vector2f & target);
	int bulletIndex = -1;

	bool canFire = false;
	float cooldown = 1;
	float coolTimer = 0;

	vector<shared_ptr<Bullet>> getBullets();
	shared_ptr<Enemy> m_enemy;

	////////////////////////////////////////////////////////////
	/// Upgrades the turret
	///
	////////////////////////////////////////////////////////////
	void upgrade(int num);
	int level = 1;
	Texture upgradeOne;
	Texture upgradeTwo;

private:
	//bool containsTower = false;
	SoundManager fired;
	vector<shared_ptr<CannonBall>> ammunition;
	//QuaternionC m_quaternion;
	Vector2f m_target;
};

#endif