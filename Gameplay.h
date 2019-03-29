////////////////////////////////////////////////////////////
//
// Created by Dale.
// Worked on by Connor, Emre and Jason
//
////////////////////////////////////////////////////////////
#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML\Graphics.hpp>
#include "Grid.h"
#include "Overlay.h"
#include "Wall.h"
#include "Turret.h"
#include "Button.h"
//#include "Bullet.h" //////////////////////////////////
#include "BaseTower.h"
#include "Portal.h"
#include "CheckShaders.h"
#include "Enemy.h"
#include "EnemyWalking.h"
#include "SoundManager.h"
#include "EnemyFlying.h"
#include "EnemyMounted.h"
#include "PathFinder.h"
#include "Game.h"
#include "GameData.h"
#include "HUD.h"
#include "Cursor.h"
#include <memory>
using namespace std;
using namespace sf;

class Gameplay
{
public:

	////////////////////////////////////////////////////////////
	/// Default constructor
	///
	////////////////////////////////////////////////////////////
	 Gameplay();

	 ////////////////////////////////////////////////////////////
	 /// Overloaded constructor
	 ///
	 ////////////////////////////////////////////////////////////
	Gameplay(shared_ptr<GameData> &data);

	////////////////////////////////////////////////////////////
	/// Updates gameplay
	///
	////////////////////////////////////////////////////////////
	void update(shared_ptr<Cursor> &cursor);

	////////////////////////////////////////////////////////////
	/// Draws the objects
	///
	////////////////////////////////////////////////////////////
	void render(RenderWindow & window);

	////////////////////////////////////////////////////////////
	/// Checks the path, including an unplaced wall
	// (to make sure you dont block the only path)
	///
	////////////////////////////////////////////////////////////
	void checkPath(shared_ptr<Cursor> &cursor); 

	////////////////////////////////////////////////////////////
	/// Checks path so normal enemies can get the nodes
	///
	////////////////////////////////////////////////////////////
	void checkPath(); 

	////////////////////////////////////////////////////////////
	/// Sets the wall onto the grid
	///
	////////////////////////////////////////////////////////////
	void wallMaker(shared_ptr<Cursor> &cursor);

	////////////////////////////////////////////////////////////
	/// Sets the turret onto the grid
	///
	////////////////////////////////////////////////////////////
	void turretMaker(shared_ptr<Cursor> &cursor);

	////////////////////////////////////////////////////////////
	/// Sets the tesla onto the grid
	///
	////////////////////////////////////////////////////////////
	void teslaMaker(shared_ptr<Cursor> &cursor);

	////////////////////////////////////////////////////////////
	/// Removes a building object from the grid 
	///
	////////////////////////////////////////////////////////////
	void removeBuildings(shared_ptr<Cursor> &cursor);

	////////////////////////////////////////////////////////////
	/// Selects a building on the grid
	///
	////////////////////////////////////////////////////////////
	void selectBuilding(shared_ptr<Cursor> &cursor);

	////////////////////////////////////////////////////////////
	/// Upgrades the turret or the tesla based on it's level
	///
	////////////////////////////////////////////////////////////
	void upgradeTowers(shared_ptr<Cursor> &cursor);

	////////////////////////////////////////////////////////////
	/// Resets all variables when the game goes back to main menu
	///
	////////////////////////////////////////////////////////////
	void theBigReset();

	shared_ptr<GameData> m_data;
	Grid m_grid; //tile container
	Overlay battleground;
	Overlay background;
	Label upgradeLabel;
	BaseTower baseTower;
	vector<shared_ptr<EnemyWalking>> walkingEnemies;
	vector<shared_ptr<EnemyFlying>> flyingEnemies;
	vector<shared_ptr<EnemyMounted>> mountedEnemies;
	float enemiesAlive = 0;
	const int MAX_ENEMIES = 10;
	Portal portal;
	PathFinder pathFinder;
	HUD hud;
	int groundNodeMap[7][5];
	int airNodeMap[7][5];
	int currentStatus = 0;
	std::vector<std::shared_ptr<Button>> button;
	std::vector < std::shared_ptr<Overlay >> statusBar;
	std::unique_ptr<Wall> tempWall;
	std::shared_ptr<Turret> tempTurret;
	std::vector<std::shared_ptr<Bullet>> bullets;
	shared_ptr<Turret> temp;
	std::shared_ptr<Tesla> tempTesla;
	enum Phase { TOWER_PLACEMENT, DEFENSE, WIN, LOSE};
	Phase currentPhase = Gameplay::TOWER_PLACEMENT;
	std::vector<std::shared_ptr<Label>> hudLabels;
	int wave = 1;
	int spawnTimer = 0;
	int const SPAWN_TIME = 45;
	int flyingCount = 0;
	int flyingMax = 0;
	int walkCount = 0;
	int walkMax = 0;
	int mountCount = 0;
	int mountMax = 0;
	bool flyDead = false;
	bool walkDead = false;
	bool mountDead = false;
	bool win = false;
	int enemyCount = 0;
	int secondsRemaining = 59;
	shared_ptr<CheckShaders> shaders;
	SoundManager wallPlaced;
	SoundManager turretPlaced;
	SoundManager teslaPlaced;
	SoundManager upgraded;
	SoundManager spawnSound;
	SoundManager waveStart;
private:



};

#endif