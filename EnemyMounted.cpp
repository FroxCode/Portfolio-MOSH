//Created by Cmag
#include "EnemyMounted.h"

EnemyMounted::EnemyMounted(){};
EnemyMounted::~EnemyMounted(){};

EnemyMounted::EnemyMounted(string const &texture, string const &deathSnd, vector<shared_ptr<Vector2f>> nodes) :
Enemy(texture, deathSnd, nodes)
{
	m_velocity = 60.0f;
	health = 650;
	m_damage = 300;
}