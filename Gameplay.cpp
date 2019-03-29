
#include "Gameplay.h"
#include <iostream>
#include <string>
Gameplay::Gameplay(shared_ptr<GameData> &data) :
portal(Vector2f(data->portalPositionX, data->portalPositionY), data->portalImage, 0), //initialise portal
baseTower(data, 0), //init base tower
hud(data), //init hud
upgradeLabel(data->font, "Cost: ", Vector2f(580, 630), 15),
m_data(data)
{
	for (int y = 0; y < 5; y++)
	{ //initialise map as empty
		for (int x = 0; x < 7; x++)
		{ 
			groundNodeMap[x][y] = 0;
			airNodeMap[x][y] = 0;
		}
	}
	

	m_grid.initialise(5, 7, 304, 120);//create grid

	//Initialise all in game assets 
	battleground.reCreate("assets/Overlays/battleground.png", Vector2f(208, 120));
	shared_ptr<Button> tempBtn = make_shared<Button>("", Vector2f(1150, 165), data->font, "assets/wallButton.png", "assets/button_click.wav", data->screenWidth, data->screenHeight, 15, false);
	button.push_back(tempBtn);
	tempBtn = make_shared<Button>("", Vector2f(1150, 315), data->font, "assets/turretButton.png", "assets/button_click.wav", data->screenWidth, data->screenHeight, 10, false);
	button.push_back(tempBtn);
	tempBtn = make_shared<Button>("", Vector2f(1150, 465), data->font, "assets/teslaButton.png", "assets/button_click.wav", data->screenWidth, data->screenHeight, 10, false);
	button.push_back(tempBtn);
	tempBtn = make_shared<Button>("", Vector2f(1045, 620), data->font, "assets/readybutton.png", "assets/button_click.wav", data->screenWidth, data->screenHeight, 10, false);
	button.push_back(tempBtn);
	tempBtn = make_shared<Button>("", Vector2f(800, 617), data->font, "assets/upgradeButton.png", "assets/button_click.wav", data->screenWidth, data->screenHeight, 10, false);
	button.push_back(tempBtn);
	tempBtn = make_shared<Button>("", Vector2f(800, 675), data->font, "assets/removeButton.png", "assets/button_click.wav", data->screenWidth, data->screenHeight, 10, false);
	button.push_back(tempBtn);

	for (int i = 0; i < 8; i++)
	{
		shared_ptr<Overlay> tempOver = make_shared<Overlay>();
		statusBar.push_back(tempOver);
	}
	statusBar.at(0)->reCreate("assets/Overlays/empty status.png", Vector2f(304, 600));
	statusBar.at(1)->reCreate("assets/Overlays/wall status.png", Vector2f(304, 600));
	statusBar.at(2)->reCreate("assets/Overlays/turret status.png", Vector2f(304, 600));
	statusBar.at(3)->reCreate("assets/Overlays/turret2 status.png", Vector2f(304, 600));
	statusBar.at(4)->reCreate("assets/Overlays/turret3 status.png", Vector2f(304, 600));
	statusBar.at(5)->reCreate("assets/Overlays/tesla status.png", Vector2f(304, 600));
	statusBar.at(6)->reCreate("assets/Overlays/tesla2 status.png", Vector2f(304, 600));
	statusBar.at(7)->reCreate("assets/Overlays/tesla3 status.png", Vector2f(304, 600));

	currentStatus = 0; //current status bar to display

	//set enemies in the first wave
	walkMax = m_data->walkingNum[wave - 1];
	flyingMax = m_data->flyingNum[wave - 1];
	mountMax = m_data->mountedNum[wave - 1];

	//set hud properties
	Vector2f hudPositions[]{Vector2f(data->screenWidth / 2, data->screenHeight / 100 * 8), Vector2f(data->screenWidth / 2, data->screenHeight / 100 * 8), Vector2f(data->screenWidth / 100 * 10, data->screenHeight / 100 * 5), Vector2f(data->screenWidth / 100 * 10, data->screenHeight / 100 * 10),
		Vector2f(data->screenWidth / 100 * 10, data->screenHeight / 100 * 35), Vector2f(data->screenWidth / 100 * 10, data->screenHeight / 100 * 49), Vector2f(data->screenWidth / 100 * 10, data->screenHeight / 100 * 65)};
	string settingsStrings[]{"Setup", "Wave " + to_string(wave), "Tokens: " + to_string(hud.m_tokens), "Credits: " + to_string(hud.m_credits), to_string(walkMax), to_string(flyingMax), to_string(mountMax)};
	for (int i = 0; i < 7; i++)
	{
		shared_ptr<Label> tempLab = make_shared<Label>("assets/m12.ttf", settingsStrings[i], hudPositions[i], 20);
		hudLabels.push_back(tempLab);
	}
	hud.add(m_data->tokens[wave - 1], 1);
	hud.add(m_data->credits[wave - 1], 2);
	hudLabels.at(2)->setString("Tokens: " + to_string(hud.m_tokens));
	hudLabels.at(3)->setString("Credits: " + to_string(hud.m_credits));

	//init shaders
	shaders = make_shared<CheckShaders>();
	shaders->initalize();
	baseTower.shaders = shaders;

	//init sounds
	wallPlaced.reCreate("assets/wallDeploy.wav", 70);
	turretPlaced.reCreate("assets/turretDeploy.wav", 70);
	teslaPlaced.reCreate("assets/teslaDeploy.wav", 70);
	upgraded.reCreate("assets/upgraded.wav", 60);
	spawnSound.reCreate("assets/portalSpawn.wav", 60);
	waveStart.reCreate("assets/waveStart.wav", 90);
}


void Gameplay::update(shared_ptr<Cursor> &cursor)
{

	m_grid.update(cursor->m_position, currentPhase);
	for (int i = 0; i < 6; i++)
	{ //button FX
		if (button.at(i)->getGlobalBounds().contains(Vector2i(cursor->m_position)))
		{
			if (button.at(i)->currentState == Button::HELD && !cursor->ctrlButtons.at(0))
			{
				button.at(i)->currentState = Button::RELEASED;
			}
			if (button.at(i)->currentState != Button::RELEASED)
			{
				button.at(i)->currentState = Button::HIGHLIGHTED;
			}
			if (cursor->ctrlButtons.at(0))
			{
				button.at(i)->currentState = Button::HELD;
			}

		}
		else
		{
			button.at(i)->currentState = Button::UNSELECTED;
		}
		button.at(i)->update();
	}
	if (baseTower.m_health <= 0)
	{ //lose condition
		currentPhase = LOSE;
	}
	if (currentPhase == TOWER_PLACEMENT)
	{ //Setup phase

		wallMaker(cursor);
		turretMaker(cursor);
		teslaMaker(cursor);

		if (baseTower.m_health <= 0)
			{ //lose condition
				currentPhase = LOSE;
			}
		if ((button.at(0)->clicked || cursor->ctrlButtons.at(3)) && tempWall == nullptr && tempTurret == nullptr && tempTesla == nullptr && hud.m_tokens - 1 >= 0)
		{
			//create wall on cursor
			tempWall = make_unique<Wall>(cursor->m_position, "assets/wallOct.png", 0);
			tempWall->m_sprite.setColor(Color(255, 255, 255, 155));
			cout << "wall created" << endl;
			hud.subtract(1, 1);
			hudLabels.at(2)->setString("Tokens: " + to_string(hud.m_tokens));
		}
		if ((button.at(1)->clicked || cursor->ctrlButtons.at(4)) && tempTurret == nullptr && tempWall == nullptr && tempTesla == nullptr && hud.m_credits - 1500 >= 0)

		{ //create turret
			tempTurret = make_shared<Turret>(cursor->m_position, "assets/Towers/turret1.png", 2);
			tempTurret->m_sprite.setColor(Color(255, 255, 255, 155));
			cout << "turret created" << endl;
			hud.subtract(1500, 2);
			hudLabels.at(3)->setString("Credits: " + to_string(hud.m_credits));
		}
		if ((button.at(2)->clicked || cursor->ctrlButtons.at(5)) && tempTurret == nullptr && tempWall == nullptr && tempTesla == nullptr && hud.m_credits - 2000 >= 0)
		{ //create tesla
			tempTesla = make_shared<Tesla>(cursor->m_position, "assets/Towers/tesla1.png", 1);
			tempTesla->m_sprite.setColor(Color(255, 255, 255, 155));
			cout << "tesla created" << endl;
			hud.subtract(2000, 2);
			hudLabels.at(3)->setString("Credits: " + to_string(hud.m_credits));
		}
		if (button.at(3)->clicked || cursor->ctrlButtons.at(7))
		{ //This is basically an initialiser function for the defending phase
			waveStart.playSingle();
			currentPhase = DEFENSE;
			tempTesla = nullptr;
			tempTurret = nullptr;
			tempWall = nullptr;
			
			for (int i = 0; i < 7 * 5; i++)
			{ //deselects all towers
				if (m_grid.tiles.at(i)->m_wall != nullptr)
				{
					m_grid.tiles.at(i)->m_wall->is_Selected = false;
					m_grid.tiles.at(i)->m_wall->m_sprite.setColor(Color(255, 255, 255, 255));
					if (m_grid.tiles.at(i)->m_wall->m_turret != nullptr)
					{
						m_grid.tiles.at(i)->m_wall->m_turret->is_Selected = false;
						m_grid.tiles.at(i)->m_wall->m_turret->m_sprite.setColor(Color(255, 255, 255, 255));
					}
					if (m_grid.tiles.at(i)->m_wall->m_tesla != nullptr)
					{
						m_grid.tiles.at(i)->m_wall->m_tesla->is_Selected = false;
						m_grid.tiles.at(i)->m_wall->m_tesla->m_sprite.setColor(Color(255, 255, 255, 255));
					}
				}
			}
				checkPath(); //calculate path

				//remake enemies
				walkingEnemies.clear();
				walkingEnemies.shrink_to_fit();
				flyingEnemies.clear();
				flyingEnemies.shrink_to_fit();
				mountedEnemies.clear();
				mountedEnemies.shrink_to_fit();
				for (int i = 0; i < 10; i++)
				{ 
					shared_ptr<EnemyWalking> tempWalker = make_shared<EnemyWalking>("assets/enemyWalkingSS.png", "assets/walkDead.wav", pathFinder.getGroundNodes());
					walkingEnemies.push_back(tempWalker);

					shared_ptr<EnemyFlying> tempFlyer = make_shared<EnemyFlying>("assets/flyGuySpritesheet.png", "assets/flyDead.wav", pathFinder.getAirNodes());
					flyingEnemies.push_back(tempFlyer);

					shared_ptr<EnemyMounted> tempMounted = make_shared<EnemyMounted>("assets/mountedEnemySS.png", "assets/mountDead.wav", pathFinder.getGroundNodes());
					mountedEnemies.push_back(tempMounted);
				}

				hudLabels.at(1)->setString("Wave " + to_string(wave));



			}
			
			selectBuilding(cursor);
			removeBuildings(cursor);
			upgradeTowers(cursor);

		}
		else if (currentPhase == DEFENSE)
		{ //if enemies are attacking
			

			portal.update();
			spawnTimer++;
			if (spawnTimer >= SPAWN_TIME)
			{ //spawn enemies, 1 by 1, type by type
				spawnTimer = 0;
				if (walkCount < m_data->walkingNum[wave - 1])
				{
					if (walkingEnemies.at(walkCount)->m_isAlive == false)
					{

						walkingEnemies.at(walkCount)->m_isAlive = true;
						walkCount++;
						spawnSound.playSingle();
					}
				}
				else if (flyingCount < m_data->flyingNum[wave - 1])
				{
					if (flyingEnemies.at(flyingCount)->m_isAlive == false)
					{
						flyingEnemies.at(flyingCount)->m_isAlive = true;
						flyingCount++;
						spawnSound.playSingle();
					}
				}
				else if (mountCount < m_data->mountedNum[wave - 1])
				{
					if (mountedEnemies.at(mountCount)->m_isAlive == false)
					{
						mountedEnemies.at(mountCount)->m_isAlive = true;
						mountCount++;
						spawnSound.playSingle();
					}
				}
			}

			//update enemies
			for (int i = 0; i < walkingEnemies.size(); i++)
			{
				if (!walkingEnemies.at(i)->m_isAlive) continue;
				else { walkingEnemies.at(i)->update(); }
				if (walkingEnemies.at(i)->state == walkingEnemies.at(i)->Attacking)
				{ //if an enemy hits the base, damage the base tower and then kill the enemy
					baseTower.subtractHealth(walkingEnemies.at(i)->m_damage);
					walkingEnemies.at(i)->state = walkingEnemies.at(i)->Death;
					walkMax -= 1;
					hudLabels.at(4)->setString(to_string(walkMax));
				}

			}
			for (int i = 0; i < flyingEnemies.size(); i++)
			{
				if (!flyingEnemies.at(i)->m_isAlive) continue;
				else { flyingEnemies.at(i)->update(); }
				if (flyingEnemies.at(i)->state == flyingEnemies.at(i)->Attacking)
				{
					baseTower.subtractHealth(flyingEnemies.at(i)->m_damage);
					flyingEnemies.at(i)->state = flyingEnemies.at(i)->Death;
					flyingMax -= 1;
					hudLabels.at(5)->setString(to_string(flyingMax));
				}
			}
			for (int i = 0; i < mountedEnemies.size(); i++)
			{
				if (!mountedEnemies.at(i)->m_isAlive) continue;
				else { mountedEnemies.at(i)->update(); }
				if (mountedEnemies.at(i)->state == mountedEnemies.at(i)->Attacking)
				{
					baseTower.subtractHealth(mountedEnemies.at(i)->m_damage);
					mountedEnemies.at(i)->state = mountedEnemies.at(i)->Death;
					mountMax -= 1;
					hudLabels.at(6)->setString(to_string(mountMax));
				}
			}



			if (currentPhase == DEFENSE && cursor->m_position.x > 304 && cursor->m_position.x < 976 && cursor->m_position.y > 120 && cursor->m_position.y < 600)
			{ //change the cursor image if you can shoot the base cannon
				cursor->crosshair = true;
				baseTower.setTowerRotationAngle(cursor->m_position);
				baseTower.rotateTower();
				if (cursor->ctrlButtons.at(0))
				{
					baseTower.fire(Vector2f(cursor->m_position));
				}
			}
			else
			{
				cursor->crosshair = false;
			}

			bullets.clear();
			bullets.shrink_to_fit();

			//update base tower
			baseTower.update();
			for (int i = 0; i < baseTower.getBullets().size(); i++)
			{//get base tower bullets
				bullets.push_back(baseTower.getBullets().at(i));
			}
			for (int i = 0; i < 7 * 5; i++)
			{
				if (m_grid.tiles.at(i)->m_wall != nullptr && m_grid.tiles.at(i)->m_wall->m_turret != nullptr)
				{ //get turret bullets
					for (int j = 0; j < m_grid.tiles.at(i)->m_wall->m_turret->getBullets().size(); j++)
					{
						bullets.push_back(m_grid.tiles.at(i)->m_wall->m_turret->getBullets().at(j));
					}
				}
				if (m_grid.tiles.at(i)->m_wall != nullptr && m_grid.tiles.at(i)->m_wall->m_tesla != nullptr)
				{ //get tesla bullets
					for (int j = 0; j < m_grid.tiles.at(i)->m_wall->m_tesla->getBullets().size(); j++)
					{
						bullets.push_back(m_grid.tiles.at(i)->m_wall->m_tesla->getBullets().at(j));
					}
				}
			}

			//targeting
			for (int i = 0; i < 7 * 5; i++)
			{
				if (m_grid.tiles.at(i)->m_wall != nullptr && m_grid.tiles.at(i)->m_wall->m_turret != nullptr)
				{//if theres a wall, and a turret on the wall
					for (int j = 0; j < MAX_ENEMIES; j++)
					{//priority targeting for turret

						if (mountedEnemies.at(j)->m_isAlive && m_grid.tiles.at(i)->m_wall->m_turret->m_circle.getGlobalBounds().contains(mountedEnemies.at(j)->m_position.x, mountedEnemies.at(j)->m_position.y))
						{
							m_grid.tiles.at(i)->m_wall->m_turret->targetEnemy(mountedEnemies.at(j));
						}
						else if (flyingEnemies.at(j)->m_isAlive && m_grid.tiles.at(i)->m_wall->m_turret->m_circle.getGlobalBounds().contains(flyingEnemies.at(j)->m_position.x, flyingEnemies.at(j)->m_position.y))
						{
							m_grid.tiles.at(i)->m_wall->m_turret->targetEnemy(flyingEnemies.at(j));
						}

						else if (walkingEnemies.at(j)->m_isAlive && m_grid.tiles.at(i)->m_wall->m_turret->m_circle.getGlobalBounds().contains(walkingEnemies.at(j)->m_position.x, walkingEnemies.at(j)->m_position.y))
						{
							m_grid.tiles.at(i)->m_wall->m_turret->targetEnemy(walkingEnemies.at(j));
						}
					}
				}
				if (m_grid.tiles.at(i)->m_wall != nullptr && m_grid.tiles.at(i)->m_wall->m_tesla != nullptr)
				{
					for (int j = 0; j < MAX_ENEMIES; j++)
					{//priority for tesla
						if (flyingEnemies.at(j)->m_isAlive && m_grid.tiles.at(i)->m_wall->m_tesla->m_circle.getGlobalBounds().contains(flyingEnemies.at(j)->m_position.x, flyingEnemies.at(j)->m_position.y))
						{
							m_grid.tiles.at(i)->m_wall->m_tesla->targetEnemy(flyingEnemies.at(j));
						}

						else if (walkingEnemies.at(j)->m_isAlive && m_grid.tiles.at(i)->m_wall->m_tesla->m_circle.getGlobalBounds().contains(walkingEnemies.at(j)->m_position.x, walkingEnemies.at(j)->m_position.y))
						{
							m_grid.tiles.at(i)->m_wall->m_tesla->targetEnemy(walkingEnemies.at(j));
						}
						else if (mountedEnemies.at(j)->m_isAlive && m_grid.tiles.at(i)->m_wall->m_tesla->m_circle.getGlobalBounds().contains(mountedEnemies.at(j)->m_position.x, mountedEnemies.at(j)->m_position.y))
						{
							m_grid.tiles.at(i)->m_wall->m_tesla->targetEnemy(mountedEnemies.at(j));
						}
					}
				}
			}

			//check bullet collision against enemies that are alive
			for (int i = 0; i < bullets.size(); i++)
			{
				for (int j = 0; j < flyingEnemies.size(); j++)
				{

					if (flyingEnemies.at(j)->m_isAlive && flyingEnemies.at(j)->bounds.contains(Vector2i(bullets.at(i)->m_position)))
					{
						flyingEnemies.at(j)->health -= (bullets.at(i)->damage);
						if (flyingEnemies.at(j)->health <= 0)
						{
							flyingMax -= 1;
							hudLabels.at(5)->setString(to_string(flyingMax));
						}
						bullets.at(i)->is_alive = false;
						if (bullets.at(i)->type == 2 && flyingEnemies.at(j)->slowed == false)
						{
							flyingEnemies.at(j)->slow();
						}
					}
				}
				for (int j = 0; j < walkingEnemies.size(); j++)
				{
					if (walkingEnemies.at(j)->m_isAlive && walkingEnemies.at(j)->bounds.contains(Vector2i(bullets.at(i)->m_position)))
					{
						walkingEnemies.at(j)->health -= (bullets.at(i)->damage);
						if (walkingEnemies.at(j)->health <= 0)
						{
							walkMax -= 1;

							hudLabels.at(4)->setString(to_string(walkMax));
						}
						bullets.at(i)->is_alive = false;
						if (bullets.at(i)->type == 2 && walkingEnemies.at(j)->slowed == false)
						{
							walkingEnemies.at(j)->slow();
						}
					}
				}
				for (int j = 0; j < mountedEnemies.size(); j++)
				{
					if (mountedEnemies.at(j)->m_isAlive && mountedEnemies.at(j)->bounds.contains(Vector2i(bullets.at(i)->m_position)))
					{

						mountedEnemies.at(j)->health -= (bullets.at(i)->damage);
						if (mountedEnemies.at(j)->health <= 0)
						{
							mountMax -= 1;
							hudLabels.at(6)->setString(to_string(mountMax));
						}
						bullets.at(i)->is_alive = false;
						if (bullets.at(i)->type == 2 && mountedEnemies.at(j)->slowed == false)
						{
							mountedEnemies.at(j)->slow();
						}
					}
				}



			}

			shaders->update(); //update shader effects

			
			if (walkMax + flyingMax + mountMax <= 0)
			{ //if the wave is completed, advance
				currentPhase = TOWER_PLACEMENT;
				wave += 1;
				if (wave > 10) //win condition
				{
					currentPhase = WIN;
					
				}

				//add credits, tokens
				hud.add(m_data->tokens[wave - 1], 1);
				hud.add(m_data->credits[wave - 1], 2);
				hudLabels.at(2)->setString("Tokens: " + to_string(hud.m_tokens));
				hudLabels.at(3)->setString("Credits: " + to_string(hud.m_credits));

				//reset enemy counters
				walkMax = 0;
				flyingMax = 0;
				mountMax = 0;
				walkMax = m_data->walkingNum[wave - 1];
				flyingMax = m_data->flyingNum[wave - 1];
				mountMax = m_data->mountedNum[wave - 1];
				hudLabels.at(4)->setString(to_string(walkMax));
				hudLabels.at(5)->setString(to_string(flyingMax));
				hudLabels.at(6)->setString(to_string(mountMax));
				walkCount = 0;
				flyingCount = 0;
				mountCount = 0;

				//remove turret and teslas targets
				for (int i = 0; i < 5 * 7; i++)
				{
					if (m_grid.tiles.at(i)->m_wall != nullptr && m_grid.tiles.at(i)->m_wall->m_turret != nullptr && m_grid.tiles.at(i)->m_wall->m_turret->m_enemy != nullptr)
					{
						m_grid.tiles.at(i)->m_wall->m_turret->m_enemy = nullptr;
					}
					if (m_grid.tiles.at(i)->m_wall != nullptr && m_grid.tiles.at(i)->m_wall->m_tesla != nullptr && m_grid.tiles.at(i)->m_wall->m_tesla->m_enemy != nullptr)
					{
						m_grid.tiles.at(i)->m_wall->m_tesla->m_enemy = nullptr;
					}
				}
			}
		}
	}

void Gameplay::render(RenderWindow & window)
{ //render all objects
	background.render(window);
	battleground.render(window);
	portal.render(window);
	
	baseTower.render(window);
	m_grid.render(window);
	for (int i = 2; i < 7; i++)
	{
		hudLabels.at(i)->render(window);
	}
	for (int i = 0; i < 4; i++)
	{
		button.at(i)->render(window);
	}
	if (tempWall != nullptr)
	{
		tempWall->render(window);
	}
	if (tempTurret != nullptr)
	{
		tempTurret->render(window);
	}
	if (tempTesla != nullptr)
	{
		tempTesla->render(window);
	}	

	if (currentPhase == DEFENSE)
	{
		hudLabels.at(1)->render(window);
		for (int i = 0; i < walkingEnemies.size(); i++)
		{
			if (!walkingEnemies.at(i)->m_isAlive) continue;
			else{walkingEnemies.at(i)->render(window);}
		}
		for (int i = 0; i < flyingEnemies.size(); i++)
		{
			if (!flyingEnemies.at(i)->m_isAlive) continue;
			else{flyingEnemies.at(i)->render(window);}
		}
		for (int i = 0; i < mountedEnemies.size(); i++)
		{
			if (!mountedEnemies.at(i)->m_isAlive) continue;
			else{ mountedEnemies.at(i)->render(window); }
		}
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets.at(i)->render(window);
		}
		shaders->render(window);
	}
	else if (currentPhase == TOWER_PLACEMENT)
	{
		statusBar.at(currentStatus)->render(window);
		hudLabels.at(0)->render(window);


		for (int i = 0; i < 35; i++)		//Change colour if selected
		{
			//Turret
			if (m_grid.tiles.at(i)->m_wall != nullptr 
				&& m_grid.tiles.at(i)->m_wall->m_turret != nullptr && m_grid.tiles.at(i)->m_wall->m_turret->is_Selected)
			{
				button.at(4)->render(window);
				button.at(5)->render(window);
				m_grid.tiles.at(i)->m_wall->m_turret->m_sprite.setColor(Color(255, 255, 0, 180));
				upgradeLabel.render(window);
			}
			else if (m_grid.tiles.at(i)->m_wall != nullptr && m_grid.tiles.at(i)->m_wall->m_turret != nullptr && !m_grid.tiles.at(i)->m_wall->m_turret->is_Selected)
			{
				m_grid.tiles.at(i)->m_wall->m_turret->m_sprite.setColor(Color(255, 255, 255, 255));
			}
			//Tesla
			if (m_grid.tiles.at(i)->m_wall != nullptr
				&& m_grid.tiles.at(i)->m_wall->m_tesla != nullptr && m_grid.tiles.at(i)->m_wall->m_tesla->is_Selected)
			{
				button.at(4)->render(window);
				button.at(5)->render(window);
				m_grid.tiles.at(i)->m_wall->m_tesla->m_sprite.setColor(Color(0, 255, 255, 180));
				upgradeLabel.render(window);
			}
			else if (m_grid.tiles.at(i)->m_wall != nullptr && m_grid.tiles.at(i)->m_wall->m_tesla != nullptr && !m_grid.tiles.at(i)->m_wall->m_tesla->is_Selected)
			{
				m_grid.tiles.at(i)->m_wall->m_tesla->m_sprite.setColor(Color(255, 255, 255, 255));
			}
			//Wall
			if (m_grid.tiles.at(i)->m_wall != nullptr && m_grid.tiles.at(i)->m_wall->is_Selected)
			{
				button.at(5)->render(window);
				m_grid.tiles.at(i)->m_wall->m_sprite.setColor(Color(255, 0, 255, 180));
			}
			else if (m_grid.tiles.at(i)->m_wall != nullptr && !m_grid.tiles.at(i)->m_wall->is_Selected)
			{
				m_grid.tiles.at(i)->m_wall->m_sprite.setColor(Color(255, 255, 255, 255));
			}
		}
	}
	
}

void Gameplay::checkPath(shared_ptr<Cursor> &cursor)
{ //checks the path to the base tower from the portal, including the cursors position as a path blocker
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			groundNodeMap[x][y] = 0;
			if (m_grid.tiles.at(x * 5 + y)->containsWall) //wall blocks path
			{
				groundNodeMap[x][y] = 1;
			}
			if (m_grid.tiles.at(x * 5 + y)->bounds.contains(Vector2i(cursor->m_position))) //cursor blocks path
			{
				groundNodeMap[x][y] = 1;
			}
		}
	}
	pathFinder.findPath(groundNodeMap); //find nodes for ground enemies
	pathFinder.setGroundNodes(pathFinder.getFoundNodes());
}
void Gameplay::checkPath()
{ //checks ground nodes and air nodes (air avoids empty walls)
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			groundNodeMap[x][y] = 0;
			if (m_grid.tiles.at(x * 5 + y)->containsWall)
			{
				groundNodeMap[x][y] = 1;
			}
		}
	}

	pathFinder.findPath(groundNodeMap);
	pathFinder.setGroundNodes(pathFinder.getFoundNodes());
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			airNodeMap[x][y] = 0;
			if (m_grid.tiles.at(x * 5 + y)->containsWall &&
				(m_grid.tiles.at(x * 5 + y)->m_wall->containsTurret || m_grid.tiles.at(x * 5 + y)->m_wall->containsTesla))
			{
				airNodeMap[x][y] = 1;
			}
		}
	}

	pathFinder.findPath(airNodeMap);
	pathFinder.setAirNodes(pathFinder.getFoundNodes());

}
void Gameplay::wallMaker(shared_ptr<Cursor> &cursor)
{ //places a wall
	if (tempWall != nullptr)
	{
		tempWall->setPosition(cursor->m_position);
		for (int i = 0; i < 7 * 5; i++)
		{
			if (tempWall != nullptr) //stops loop from continuing if wall gets assigned
			{

				if (m_grid.tiles.at(i)->bounds.contains(Vector2i(cursor->m_position)) && m_grid.tiles.at(i)->m_wall == nullptr && m_grid.tiles.at(i)->canHaveWall)
				{
					checkPath(cursor);
					m_grid.tiles.at(i)->m_rect.setFillColor(Color(0, 255, 0, 128));
					tempWall->setPosition(sf::Vector2f(m_grid.tiles.at(i)->m_position.x + tempWall->m_sprite.getGlobalBounds().width / 2 - 16,
						m_grid.tiles.at(i)->m_position.y + tempWall->m_sprite.getGlobalBounds().height / 2 - 16)); //lock the wall location to the grid

					if (cursor->ctrlButtons.at(0) && m_grid.tiles.at(i)->m_wall == nullptr && pathFinder.hasPath) // make sure the tile has no wall
					{
						tempWall->setPosition(sf::Vector2f(m_grid.tiles.at(i)->m_position.x + tempWall->m_sprite.getGlobalBounds().width / 2,
							m_grid.tiles.at(i)->m_position.y + tempWall->m_sprite.getGlobalBounds().height / 2));
						tempWall->m_sprite.setColor(Color(255, 255, 255, 255));
						m_grid.tiles.at(i)->m_wall = std::move(tempWall); //assign the wall to the tile selected
						m_grid.tiles.at(i)->containsWall = true;
						wallPlaced.playSingle();
					}
					else if (!pathFinder.hasPath)
					{
						m_grid.tiles.at(i)->m_rect.setFillColor(Color(255, 0, 0, 128));
					}
				}
				else if ((m_grid.tiles.at(i)->bounds.contains(Vector2i(cursor->m_position)) && m_grid.tiles.at(i)->m_wall != nullptr) || (m_grid.tiles.at(i)->bounds.contains(Vector2i(cursor->m_position)) && m_grid.tiles.at(i)->canHaveWall == false))
				{
					tempWall->setPosition(sf::Vector2f(m_grid.tiles.at(i)->m_position.x + tempWall->m_sprite.getGlobalBounds().width / 2 - 16,
						m_grid.tiles.at(i)->m_position.y + tempWall->m_sprite.getGlobalBounds().height / 2 - 16)); //lock the wall location to the grid
					m_grid.tiles.at(i)->m_rect.setFillColor(Color(255, 0, 0, 128));
				}
				else
				{
					m_grid.tiles.at(i)->m_rect.setFillColor(Color(255, 255, 255, 0));
				}
			}
			else
			{
				break;
			}
		}
	}
}

void Gameplay::turretMaker(shared_ptr<Cursor> &cursor)
{//places a turret

	if (tempTurret != nullptr)
	{
		tempTurret->setPosition(cursor->m_position);
		for (int i = 0; i < 7 * 5; i++)
		{
			if (tempTurret != nullptr)
			{
				if (m_grid.tiles.at(i)->bounds.contains(Vector2i(cursor->m_position)) && m_grid.tiles.at(i)->m_wall == nullptr)
				{
					m_grid.tiles.at(i)->m_rect.setFillColor(Color(255, 0, 0, 128));
					tempTurret->setPosition(sf::Vector2f(m_grid.tiles.at(i)->m_position.x + tempTurret->m_sprite.getGlobalBounds().width / 2 - 16,
						m_grid.tiles.at(i)->m_position.y + tempTurret->m_sprite.getGlobalBounds().height / 2 - 16)); //lock the wall location to the grid


				}
				else if (m_grid.tiles.at(i)->bounds.contains(Vector2i(cursor->m_position)) && m_grid.tiles.at(i)->m_wall != nullptr)
				{
					m_grid.tiles.at(i)->m_rect.setFillColor(Color(0, 255, 0, 128));

					tempTurret->setPosition(sf::Vector2f(m_grid.tiles.at(i)->m_position.x + tempTurret->m_sprite.getGlobalBounds().width / 2 - 16,
						m_grid.tiles.at(i)->m_position.y + tempTurret->m_sprite.getGlobalBounds().height / 2 - 16)); //lock the wall location to the grid


					if (cursor->ctrlButtons.at(0) && !m_grid.tiles.at(i)->m_wall->containsTurret) // make sure the tile has no wall

					{
						tempTurret->setPosition(sf::Vector2f(m_grid.tiles.at(i)->m_position.x + tempTurret->m_sprite.getGlobalBounds().width / 2,
							m_grid.tiles.at(i)->m_position.y + tempTurret->m_sprite.getGlobalBounds().height / 2));
						tempTurret->m_sprite.setColor(Color(255, 255, 255, 255));
						tempTurret->is_Selected = false;
						m_grid.tiles.at(i)->m_wall->m_turret = std::move(tempTurret);//assign the wall to the tile selected
						m_grid.tiles.at(i)->m_wall->containsTurret = true;
						turretPlaced.playSingle();
						//tempWall = nullptr;

					}
					else if (m_grid.tiles.at(i)->m_wall->containsTurret)

					{
						tempTurret->setPosition(sf::Vector2f(m_grid.tiles.at(i)->m_position.x + tempTurret->m_sprite.getGlobalBounds().width / 2 - 16,
							m_grid.tiles.at(i)->m_position.y + tempTurret->m_sprite.getGlobalBounds().height / 2 - 16)); //lock the wall location to the grid
						m_grid.tiles.at(i)->m_rect.setFillColor(Color(255, 0, 0, 128));
					}
				}
				else
				{
					m_grid.tiles.at(i)->m_rect.setFillColor(Color(255, 255, 255, 0));
				}


			}
			else
			{
				break;
			}
		}
	}
}

void Gameplay::teslaMaker(shared_ptr<Cursor> &cursor)
{ //places a tesla
	if (tempTesla != nullptr)
	{
		tempTesla->setPosition(cursor->m_position);
		for (int i = 0; i < 7 * 5; i++)
		{
			if (tempTesla != nullptr)
			{

				if (m_grid.tiles.at(i)->bounds.contains(Vector2i(cursor->m_position)) && m_grid.tiles.at(i)->m_wall == nullptr)
				{
					tempTesla->setPosition(sf::Vector2f(m_grid.tiles.at(i)->m_position.x + tempTesla->m_sprite.getGlobalBounds().width / 2 - 16,
						m_grid.tiles.at(i)->m_position.y + tempTesla->m_sprite.getGlobalBounds().height / 2 - 16)); //lock the wall location to the grid
					m_grid.tiles.at(i)->m_rect.setFillColor(Color(255, 0, 0, 128));
				}
				else if (m_grid.tiles.at(i)->bounds.contains(Vector2i(cursor->m_position)) && m_grid.tiles.at(i)->m_wall != nullptr)
				{
					m_grid.tiles.at(i)->m_rect.setFillColor(Color(0, 255, 0, 128));
					tempTesla->setPosition(sf::Vector2f(m_grid.tiles.at(i)->m_position.x + tempTesla->m_sprite.getGlobalBounds().width / 2 - 16,
						m_grid.tiles.at(i)->m_position.y + tempTesla->m_sprite.getGlobalBounds().height / 2 - 16)); //lock the wall location to the grid

					if (cursor->ctrlButtons.at(0) && !m_grid.tiles.at(i)->m_wall->containsTesla) // make sure the tile has no wall

					{
						tempTesla->setPosition(sf::Vector2f(m_grid.tiles.at(i)->m_position.x + tempTesla->m_sprite.getGlobalBounds().width / 2,
							m_grid.tiles.at(i)->m_position.y + tempTesla->m_sprite.getGlobalBounds().height / 2));
						tempTesla->m_sprite.setColor(Color(255, 255, 255, 255));
						tempTesla->is_Selected = false;
						m_grid.tiles.at(i)->m_wall->m_tesla = std::move(tempTesla);//assign the wall to the tile selected
						m_grid.tiles.at(i)->m_wall->containsTesla = true;
						teslaPlaced.playSingle();
						//tempWall = nullptr;

					}
					else if (m_grid.tiles.at(i)->m_wall->containsTesla)

					{
						m_grid.tiles.at(i)->m_rect.setFillColor(Color(255, 0, 0, 128));
						tempTesla->setPosition(sf::Vector2f(m_grid.tiles.at(i)->m_position.x + tempTesla->m_sprite.getGlobalBounds().width / 2 - 16,
							m_grid.tiles.at(i)->m_position.y + tempTesla->m_sprite.getGlobalBounds().height / 2 - 16)); //lock the wall location to the grid
					}
				}
				else
				{
					m_grid.tiles.at(i)->m_rect.setFillColor(Color(255, 255, 255, 0));
				}
			}
			else
			{
				break;
			}
		}
	}
}

void Gameplay::removeBuildings(shared_ptr<Cursor> &cursor)
{ //removes an already placed building
	if (button.at(5)->clicked || cursor->ctrlButtons.at(8))
	{
		for (int i = 0; i < 35; i++)
		{
			//Wall
			if (m_grid.tiles.at(i)->m_wall != nullptr && !m_grid.tiles.at(i)->m_wall->containsTurret &&
				!m_grid.tiles.at(i)->m_wall->containsTurret && m_grid.tiles.at(i)->m_wall->is_Selected)
			{
				m_grid.tiles.at(i)->m_wall = nullptr;
				m_grid.tiles.at(i)->containsWall = false;
				hud.add(1, 1);
				hudLabels.at(2)->setString("Tokens: " + to_string(hud.m_tokens));
			}
			//Turret
			else if (m_grid.tiles.at(i)->m_wall != nullptr && m_grid.tiles.at(i)->m_wall->m_turret != nullptr
				&& m_grid.tiles.at(i)->m_wall->m_turret->is_Selected)
			{
				m_grid.tiles.at(i)->m_wall->m_turret = nullptr;
				m_grid.tiles.at(i)->m_wall->containsTurret = false;
				hud.add(1500, 2);
				hudLabels.at(3)->setString("Credits: " + to_string(hud.m_credits));
			}
			//Tesla
			else if (m_grid.tiles.at(i)->m_wall != nullptr && m_grid.tiles.at(i)->m_wall->m_tesla != nullptr
				&& m_grid.tiles.at(i)->m_wall->m_tesla->is_Selected)
			{
				m_grid.tiles.at(i)->m_wall->m_tesla = nullptr;
				m_grid.tiles.at(i)->m_wall->containsTesla = false;
				hud.add(2000, 2);
				hudLabels.at(3)->setString("Credits: " + to_string(hud.m_credits));
			}
		}
	}
}

void Gameplay::selectBuilding(shared_ptr<Cursor> &cursor)
{
	for (int i = 0; i < 7 * 5; i++)			
		//Selection of a building
	{
		//Wall
		if ((cursor->ctrlButtons.at(0) || cursor->ctrlButtons.at(7))
			&& m_grid.tiles.at(i)->m_wall != nullptr && !m_grid.tiles.at(i)->bounds.contains(Vector2i(cursor->m_position))
			&& !button.at(5)->getGlobalBounds().contains(Vector2i(cursor->m_position)))
		{
			m_grid.tiles.at(i)->m_wall->is_Selected = false;
			//currentStatus = 0;
			
		}
		if (m_grid.tiles.at(i)->bounds.contains(Vector2i(cursor->m_position)) && cursor->ctrlButtons.at(0) &&
			m_grid.tiles.at(i)->m_wall != nullptr && m_grid.tiles.at(i)->m_wall->m_turret == nullptr && m_grid.tiles.at(i)->m_wall->m_tesla == nullptr && !m_grid.tiles.at(i)->m_wall->is_Selected)
		{
			m_grid.tiles.at(i)->m_wall->is_Selected = true;
			currentStatus = 1;
		}

		//Turret
		if ((cursor->ctrlButtons.at(0) || cursor->ctrlButtons.at(7)) &&
			m_grid.tiles.at(i)->m_wall != nullptr && m_grid.tiles.at(i)->m_wall->m_turret != nullptr
			&& !m_grid.tiles.at(i)->bounds.contains(Vector2i(cursor->m_position)) && !button.at(5)->getGlobalBounds().contains(Vector2i(cursor->m_position))
			&& !button.at(4)->getGlobalBounds().contains(Vector2i(cursor->m_position)))
		{
			m_grid.tiles.at(i)->m_wall->m_turret->is_Selected = false;
			//currentStatus = 0;
		}
		if (m_grid.tiles.at(i)->bounds.contains(Vector2i(cursor->m_position)) && cursor->ctrlButtons.at(0) &&
			m_grid.tiles.at(i)->m_wall != nullptr && m_grid.tiles.at(i)->m_wall->m_turret != nullptr && !m_grid.tiles.at(i)->m_wall->m_turret->is_Selected)
		{
			m_grid.tiles.at(i)->m_wall->m_turret->is_Selected = true;
			
			if (m_grid.tiles.at(i)->m_wall->m_turret->level == 1)
			{
				upgradeLabel.setString("Cost: 2000");
				currentStatus = 2;
			}
			else if (m_grid.tiles.at(i)->m_wall->m_turret->level == 2)
			{
				upgradeLabel.setString("Cost: 3000");
				currentStatus = 3;
			}
			else if (m_grid.tiles.at(i)->m_wall->m_turret->level == 3)
			{
				upgradeLabel.setString("Cannot Upgrade");
				currentStatus = 4;
			}
		}

		//Tesla
		if ((cursor->ctrlButtons.at(0) || cursor->ctrlButtons.at(7)) &&
			m_grid.tiles.at(i)->m_wall != nullptr && m_grid.tiles.at(i)->m_wall->m_tesla != nullptr
			&& !m_grid.tiles.at(i)->bounds.contains(Vector2i(cursor->m_position)) && !button.at(5)->getGlobalBounds().contains(Vector2i(cursor->m_position))
			&& !button.at(4)->getGlobalBounds().contains(Vector2i(cursor->m_position)))
		{
			m_grid.tiles.at(i)->m_wall->m_tesla->is_Selected = false;
			//currentStatus = 0;
		}
		if (m_grid.tiles.at(i)->bounds.contains(Vector2i(cursor->m_position))
			&& cursor->ctrlButtons.at(0) &&
			m_grid.tiles.at(i)->m_wall != nullptr && m_grid.tiles.at(i)->m_wall->m_tesla != nullptr && !m_grid.tiles.at(i)->m_wall->m_tesla->is_Selected)
		{
			m_grid.tiles.at(i)->m_wall->m_tesla->is_Selected = true;
			if (m_grid.tiles.at(i)->m_wall->m_tesla->level == 1)
			{
				upgradeLabel.setString("Cost: 2500");
				currentStatus = 5;
			}
			else if (m_grid.tiles.at(i)->m_wall->m_tesla->level == 2)
			{
				upgradeLabel.setString("Cost: 3000");
				currentStatus = 6;
			}
			else if (m_grid.tiles.at(i)->m_wall->m_tesla->level == 3)
			{
				upgradeLabel.setString("Cannot Upgrade");
				currentStatus = 7;
			}
		}
	}

	//Unselect the buildings

	if (cursor->ctrlButtons.at(1))
	{

		if (tempTesla != nullptr)
		{
			tempTesla = nullptr;
			cout << "tesla deleted" << endl;
			hud.add(2000, 2);														//Refunds the cost
			hudLabels.at(3)->setString("Credits: " + to_string(hud.m_credits));
		}
		if (tempTurret != nullptr)
		{
			tempTurret = nullptr;
			cout << "turret deleted" << endl;
			hud.add(1500, 2);
			hudLabels.at(3)->setString("Credits: " + to_string(hud.m_credits));
		}
		if (tempWall != nullptr)
		{
			tempWall = nullptr;
			cout << "wall deleted" << endl;
			hud.add(1, 1);
			hudLabels.at(2)->setString("Tokens: " + to_string(hud.m_tokens));
		}
	}
}

void Gameplay::upgradeTowers(shared_ptr<Cursor> &cursor)
{//upgrade turret and tesla

	for (int i = 0; i < 35; i++)
	{
		if ((button.at(4)->clicked || cursor->ctrlButtons.at(2)) && m_grid.tiles.at(i)->m_wall != nullptr && m_grid.tiles.at(i)->m_wall->m_turret != nullptr &&
			m_grid.tiles.at(i)->m_wall->m_turret->is_Selected)
		{

			if (m_grid.tiles.at(i)->m_wall->m_turret->level == 1 && hud.m_credits - 2000 >= 0)
			{
				upgraded.playSingle();
				m_grid.tiles.at(i)->m_wall->m_turret->upgrade(m_grid.tiles.at(i)->m_wall->m_turret->level);
				hud.subtract(2000, 2);
				hudLabels.at(3)->setString("Credits: " + to_string(hud.m_credits));
				if (m_grid.tiles.at(i)->m_wall->m_turret->level == 2)
				upgradeLabel.setString("Cost: 3000");
				
			}
			else if (m_grid.tiles.at(i)->m_wall->m_turret->level == 2 && hud.m_credits - 3000 >= 0)
			{
				upgraded.playSingle();
				m_grid.tiles.at(i)->m_wall->m_turret->upgrade(m_grid.tiles.at(i)->m_wall->m_turret->level);
				hud.subtract(3000, 2);
				hudLabels.at(3)->setString("Credits: " + to_string(hud.m_credits));
				upgradeLabel.setString("Cannot Upgrade");
			}
		}
		else if ((button.at(4)->clicked || cursor->ctrlButtons.at(2)) && m_grid.tiles.at(i)->m_wall != nullptr && m_grid.tiles.at(i)->m_wall->m_tesla != nullptr &&
			m_grid.tiles.at(i)->m_wall->m_tesla->is_Selected)
		{
			
			if (m_grid.tiles.at(i)->m_wall->m_tesla->level == 1 && hud.m_credits - 2500 >= 0)
			{
				upgraded.playSingle();
				m_grid.tiles.at(i)->m_wall->m_tesla->upgrade(m_grid.tiles.at(i)->m_wall->m_tesla->level);
				hud.subtract(2500, 2);
				hudLabels.at(3)->setString("Credits: " + to_string(hud.m_credits));
				upgradeLabel.setString("Cost: 3000");
			}
			else if (m_grid.tiles.at(i)->m_wall->m_tesla->level == 2 && hud.m_credits - 3000 >= 0)
			{
				upgraded.playSingle();
				m_grid.tiles.at(i)->m_wall->m_tesla->upgrade(m_grid.tiles.at(i)->m_wall->m_tesla->level);
				hud.subtract(3000, 2);
				hudLabels.at(3)->setString("Credits: " + to_string(hud.m_credits));
				upgradeLabel.setString("Cannot Upgrade");
			}
		}
	}

}

void Gameplay::theBigReset()
{ //reset the game data
	wave = 1;
	currentPhase = TOWER_PLACEMENT;
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		flyingEnemies.clear();
		flyingEnemies.shrink_to_fit();
		walkingEnemies.clear();
		walkingEnemies.shrink_to_fit();
		mountedEnemies.clear();
		mountedEnemies.shrink_to_fit();
	}
	for (int i = 0; i < 35; i++)
	{
		m_grid.tiles.at(i)->m_wall = nullptr;
		m_grid.tiles.at(i)->containsWall = false;
	}
	hud.m_credits = 0;
	hud.m_tokens = 0;
	hud.add(m_data->tokens[wave - 1], 1);
	hud.add(m_data->credits[wave - 1], 2);
	baseTower.m_health = 2000;

	hudLabels.at(2)->setString("Tokens: " + to_string(hud.m_tokens));
	hudLabels.at(3)->setString("Credits: " + to_string(hud.m_credits));
	walkMax = 0;
	flyingMax = 0;
	mountMax = 0;
	walkCount = 0;
	flyingCount = 0;
	mountCount = 0;
	walkMax = m_data->walkingNum[wave - 1];
	flyingMax = m_data->flyingNum[wave - 1];
	mountMax = m_data->mountedNum[wave - 1];
	hudLabels.at(4)->setString(to_string(walkMax));
	hudLabels.at(5)->setString(to_string(flyingMax));
	hudLabels.at(6)->setString(to_string(mountMax));

}