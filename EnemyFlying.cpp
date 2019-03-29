//Created by Cmag
#include "EnemyFlying.h"

EnemyFlying::EnemyFlying(){};
EnemyFlying::~EnemyFlying(){};

EnemyFlying::EnemyFlying(string const &texture, string const &deathSnd, vector<shared_ptr<Vector2f>> nodes) :
Enemy(texture, deathSnd, nodes)
{
	m_velocity = 80.0f;
	health = 175;
	m_damage = 200;
}
