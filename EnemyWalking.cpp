// Created by Connor Maguire
#include "EnemyWalking.h"

EnemyWalking::EnemyWalking(){};
EnemyWalking::~EnemyWalking(){};

EnemyWalking::EnemyWalking(string const &texture, string const &deathSnd, vector<shared_ptr<Vector2f>> nodes) :
Enemy(texture, deathSnd, nodes)
{
	m_velocity = 80.0f;
	health = 250;
	m_damage = 100;
}