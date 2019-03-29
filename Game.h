////////////////////////////////////////////////////////////
//
// Created by Dale
// Worked on by Connor, Emre and Jason
//
////////////////////////////////////////////////////////////
#ifndef _GAME_H_
#define _GAME_H_
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "JSON.h"
#include "JSONValue.h"
#include "Menu.h"
#include "Gameplay.h"
#include "GameLoader.h"
#include "GameData.h"
#include <SFML/System/Clock.hpp>
#include "MoviePlayer.h"
#include "Cursor.h"
using namespace std;
using namespace sf;

class Game
{
public:
	////////////////////////////////////////////////////////////
	/// Default constructor
	///
	////////////////////////////////////////////////////////////
	Game();

	////////////////////////////////////////////////////////////
	/// Default destructor
	///
	////////////////////////////////////////////////////////////
	~Game();

	////////////////////////////////////////////////////////////
	/// The main event in game
	///
	////////////////////////////////////////////////////////////
	void run();

	////////////////////////////////////////////////////////////
	/// Controller support
	///
	////////////////////////////////////////////////////////////
	void controls();

	enum GameStates{ SPLASH, LICENSE, MAIN_MENU, MODE_SELECT, INGAME_CUTSCENE, INGAME, OPTIONS, EXTRAS, GAME_WIN, GAME_LOSE, HELP, CREDITS, PAUSE}; //Game states
	GameStates currentGameState = Game::SPLASH; //initial state
	enum GameMode{ STORY, ENDLESS };
	GameMode currentGameMode = Game::STORY;
	
	shared_ptr<Cursor> cursor;
private:
	sf::RenderWindow window; //main window
	float myTime = 0;
	sf::Clock m_clock; //for update cycles
	float const FPS = 60.0f;
	const sf::Time timePerFrame = sf::seconds(1.0f / FPS);
	sf::Time timeSinceLastUpdate = sf::Time::Zero; // update timer
	
	bool isRunning = false; //game loop bool

	
	////////////////////////////////////////////////////////////
	/// Re-initialises the object
	///
	////////////////////////////////////////////////////////////
	void initialize();
	////////////////////////////////////////////////////////////
	/// Updates the object
	///
	////////////////////////////////////////////////////////////
	void update();
	////////////////////////////////////////////////////////////
	/// Drwas the object and it's components
	///
	////////////////////////////////////////////////////////////

	void render();
	int temp = 0;
	int tempIsh = 0;
	
};
#endif;