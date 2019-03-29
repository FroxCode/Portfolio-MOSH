////////////////////////////////////////////////////////////
//
// Created by Connor
// Worked on by Dale
//
////////////////////////////////////////////////////////////
#ifndef _ENEMYMOUNTED_H_
#define _ENEMYMOUNTED_H_
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Enemy.h"

class EnemyMounted : public Enemy
{
public:
	////////////////////////////////////////////////////////////
	/// Default constructor
	///
	////////////////////////////////////////////////////////////
	EnemyMounted();
	////////////////////////////////////////////////////////////
	/// Default destructor
	///
	////////////////////////////////////////////////////////////
	~EnemyMounted();

	////////////////////////////////////////////////////////////
	/// Overloaded constructor
	///
	////////////////////////////////////////////////////////////
	EnemyMounted(string const &texture, string const &deathSnd, vector<shared_ptr<Vector2f>> nodes);

};
#endif 
