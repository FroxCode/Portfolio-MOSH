//Created by Dale Sinnott
#include "Game.h"
#include "SoundManager.h"

//vars for loading data
GameLoader gameLoader;
shared_ptr<GameData> data;
//gameplay
shared_ptr<Gameplay> game;
Game::Game() : window(sf::VideoMode(1280, 720), "Mosh") 
{ //load screen and load data
	Overlay loading;
	loading.reCreate("assets/loading.png", 1280, 720, 100, 100, true);
	loading.render(window);
	window.display();
	data = make_shared<GameData>();
	std::string jsonData;
	std::string filename = ".\\data\\GameData.json";
	JSON::loadJSONData(filename, jsonData);
	gameLoader.parseJSONData(jsonData, data);
	game = make_shared<Gameplay>(data);
	bool show = false;
	
}

Game::~Game()
{

}
//Menus
Menu mainMenu;
Menu extrasMenu;
Menu playModeMenu;
Menu optionsMenu;
Menu pauseMenu;
Menu inGameMenu;

//Splashes
Overlay splashScreen;
Overlay licenseScreen;
Overlay helpScreen;


std::vector<std::shared_ptr<Label>> settings;
std::vector<Overlay> credits;

//sounds
SoundManager menuMusic;
SoundManager endConditionSounds[2];

//animations
MoviePlayer moviePlayer("assets/Animations/AnimationIntroduction.mp4");
MoviePlayer introMov("assets/Animations/AnimationLicense.mp4"); //not used
MoviePlayer winMov("assets/Animations/AnimationsWin.mp4");
MoviePlayer loseMov("assets/Animations/AnimationLose.mp4");
void Game::run()
{
	initialize();

	Event event;
	
	while (isRunning)
	{  //MAIN GAME LOOP
		timeSinceLastUpdate += m_clock.restart();
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
			if (event.type == Event::KeyReleased)
			{
				switch (event.key.code)
				{
				case Keyboard::Escape:
					isRunning = false;
					break;
					
				default:
					break;
				}
			}
		}
		
		
		if (timeSinceLastUpdate > timePerFrame)
		{ //fixed update of 60 FPS
			
			update();
			render();
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}
}

void Game::initialize()
{ //load all in game data

	window.setMouseCursorVisible(false);
	Vector2f menuPositions[]{ Vector2f(data->screenWidth / 2, data->screenHeight / 100 * 41), Vector2f(data->screenWidth / 2, data->screenHeight / 100 * 54), Vector2f(data->screenWidth / 2, data->screenHeight / 100 * 67), Vector2f(data->screenWidth / 2, data->screenHeight / 100 * 80) };
	Vector2f extrasPositions[]{ Vector2f(data->screenWidth / 2, data->screenHeight / 100 * 41), Vector2f(data->screenWidth / 2, data->screenHeight / 100 * 54), Vector2f(data->screenWidth / 2, data->screenHeight / 100 * 67)};
	Vector2f playModePositions[]{ Vector2f(data->screenWidth / 2, data->screenHeight / 100 * 38),  Vector2f(data->screenWidth / 2, data->screenHeight / 100 * 80)};
	Vector2f optionsPositions[]{ Vector2f(data->screenWidth / 100 * 44, data->screenHeight / 100 * 33), Vector2f(data->screenWidth / 100 * 78, data->screenHeight / 100 * 33), Vector2f(data->screenWidth / 100 * 44, data->screenHeight / 100 * 53), Vector2f(data->screenWidth / 100 * 78, data->screenHeight / 100 * 53), Vector2f(1280 / 100 * 60, data->screenHeight / 100 * 80)};
	Vector2f settingsPositions[]{Vector2f(data->screenWidth / 100 * 20, data->screenHeight / 100 * 35), Vector2f(data->screenWidth / 100 * 20, data->screenHeight / 100 * 55), Vector2f(data->screenWidth / 100 * 61, data->screenHeight / 100 * 33), Vector2f(data->screenWidth / 100 * 61, data->screenHeight / 100 * 53) };
	Vector2f pausePositions[]{Vector2f(data->screenWidth / 2, data->screenHeight / 100 * 38), Vector2f(data->screenWidth / 2, data->screenHeight / 100 * 53)};
	Vector2f inGamePositions[]{Vector2f(166, 620 )};

	splashScreen.reCreate(data->splashImage, data->screenWidth, data->screenHeight, 100, 100, true);
	licenseScreen.reCreate("assets/licenseScreen.png", data->screenWidth, data->screenHeight, 100, 100, true);
	helpScreen.reCreate("assets/Overlays/helpScreen.png", data->screenWidth, data->screenHeight, 100, 100, true);

	std::string menuStrings[]{ "Play", "Options", "Extras", "Exit"};
	std::string extrasStrings[]{ "Help", "Credits", "Return"};
	std::string playModeStrings[]{"Story", "Return"};
	std::string optionsStrings[]{"down", "up", "down", "up", "Return"};
	std::string settingsStrings[]{"Music:", "SFX:", "50", "50"};
	std::string pauseStrings[]{"Resume", "Exit"};
	std::string inGameString[]{""};


	mainMenu.reCreate(4, data->menuHeading, data->font, data->menuImage, data->menuButtonImage, data->buttonSounds, data->screenWidth, data->screenHeight, menuStrings, menuPositions, 20, 60, true);
	extrasMenu.reCreate(3, data->extrasHeading, data->font, data->menuImage, data->menuButtonImage, data->buttonSounds, data->screenWidth, data->screenHeight, extrasStrings, extrasPositions, 12, 30, true);
	playModeMenu.reCreate(2, data->modeHeading, data->font, data->menuImage, data->menuButtonImage, data->buttonSounds, data->screenWidth, data->screenHeight, playModeStrings, playModePositions, 20, 30, true);
	optionsMenu.reCreate(5, data->optionsHeading, data->font, data->menuImage, data->menuButtonImage, data->buttonSounds, data->screenWidth, data->screenHeight, optionsStrings, optionsPositions, 20, 30, true);
	pauseMenu.reCreate(2, data->pauseHeading, data->font, data->menuImage, data->menuButtonImage, data->buttonSounds, data->screenWidth, data->screenHeight, pauseStrings, pausePositions, 20, 30, true);
	inGameMenu.reCreate(1, "", data->font, "assets/Overlays/BackgroundComplete2.png", data->pauseButtonImage, data->buttonSounds, data->screenWidth, data->screenHeight, inGameString, inGamePositions, 20, 20, false);

	for (int i = 0; i < 4; i++)
	{
		std::shared_ptr<Label> tempLab = std::make_shared<Label>("assets/m12.ttf", settingsStrings[i], settingsPositions[i], 30);
		settings.push_back(tempLab);
	}

	Overlay tempO;
	credits.push_back(tempO);
	Overlay temp1;
	credits.push_back(temp1);
	Overlay temp2;
	credits.push_back(temp2);

	credits.at(0).reCreate("assets/Overlays/credits1.png", 1280, 720, 100, 100, true);
	credits.at(1).reCreate("assets/Overlays/credits2.png", 1280, 720, 100, 100, true);
	credits.at(2).reCreate("assets/Overlays/credits3.png", 1280, 720, 100, 100, true);

	isRunning = true;
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true); 
	m_clock.restart();

	endConditionSounds[0].reCreate("assets/victoryMusic.wav", 100);
	endConditionSounds[1].reCreate("assets/defeatMusic.wav", 100);
	menuMusic.reCreate("assets/Music.wav", 40);
	menuMusic.playLoop();

	cursor = make_shared<Cursor>(Vector2f(640.f, 360.f), "assets/cursor.png");
}

void Game::update()
{ //update main loop depending on gamestate
	cursor->update();
	switch (currentGameState)
	{
	case Game::SPLASH:
		splashScreen.update();
		timeSinceLastUpdate += m_clock.restart();			
		myTime += timeSinceLastUpdate.asSeconds();
		if (myTime >= 3)
		{
			currentGameState = LICENSE;
			myTime = 0;
		}
		timeSinceLastUpdate = sf::Time::Zero;
		break;
	case Game::LICENSE:
		licenseScreen.update();
		timeSinceLastUpdate += m_clock.restart();
		myTime += timeSinceLastUpdate.asSeconds();
		if (myTime >= 3)
		{
			currentGameState = MAIN_MENU;
			myTime = 0;
		}
		timeSinceLastUpdate = sf::Time::Zero;
		break;
	case Game::MAIN_MENU:
		mainMenu.update(cursor);

		if (mainMenu.button.at(0)->clicked)
		{
			currentGameState = Game::MODE_SELECT;
		}
		else if (mainMenu.button.at(1)->clicked)
		{
			currentGameState = Game::OPTIONS;
		}
		else if (mainMenu.button.at(2)->clicked)
		{
			currentGameState = Game::EXTRAS;
		}
		else if (mainMenu.button.at(3)->clicked)
		{
			isRunning = false;
		}
		break;
	case Game::MODE_SELECT:
		playModeMenu.update(cursor);

		if (playModeMenu.button.at(0)->clicked)
		{
			currentGameState = Game::INGAME_CUTSCENE;
			moviePlayer.play();
			currentGameMode = GameMode::STORY;
		}
		else if (playModeMenu.button.at(1)->clicked)
		{
			currentGameState = Game::MAIN_MENU;
			
		}
		break;
	case Game::INGAME_CUTSCENE:
		moviePlayer.update();
		if (!moviePlayer.isPlaying)
		{
			currentGameState = GameStates::INGAME;
			game->currentStatus = Gameplay::TOWER_PLACEMENT;
		}
		break;
	case Game::INGAME:
		menuMusic.setVolume(20);
		inGameMenu.update(cursor);
		game->update(cursor);
		if (inGameMenu.button.at(0)->clicked || cursor->ctrlButtons.at(6))
		{
			currentGameState = Game::PAUSE;
		}
		if (game->currentPhase == Gameplay::WIN)
		{
			currentGameState = Game::GAME_WIN;
			winMov.play();
			endConditionSounds[0].playSingle();
		}
		if (game->currentPhase == Gameplay::LOSE)
		{
			currentGameState = Game::GAME_LOSE;
			loseMov.play();
			endConditionSounds[1].playSingle();
		}
		break;
	case Game::OPTIONS:
		optionsMenu.update(cursor);
		for (int i = 0; i < 2; i++)	
		{
			settings.at(i)->update();
		}
		//change volumes
		if (optionsMenu.button.at(0)->clicked)
		{
			menuMusic.adjustVolume(-1);
			for (int i = 0; i < 2; i++)
			{
				endConditionSounds[i].adjustVolume(-1);
			}
			int temp = menuMusic.getVolume();
			if (temp <= 0){
				temp = 0;
				menuMusic.setVolume(0);
				for (int i = 0; i < 2; i++)
				{
					endConditionSounds[i].setVolume(0);
				}
			}
			settings.at(2)->setString(std::to_string(temp));
		}
		else if (optionsMenu.button.at(1)->clicked)
		{
			menuMusic.adjustVolume(1);
			for (int i = 0; i < 2; i++)
			{
				endConditionSounds[i].adjustVolume(1);
			}
			int temp = menuMusic.getVolume();
			if (temp >= 100){
				temp = 100;
				menuMusic.setVolume(100);
				for (int i = 0; i < 2; i++)
				{
					endConditionSounds[i].setVolume(100);
				}
			}
			settings.at(2)->setString(std::to_string(temp));
		}
		else if (optionsMenu.button.at(2)->clicked)
		{
			optionsMenu.adjustSoundVolume(-1);
			int temp = optionsMenu.getSoundVolume();
			if (temp <= 0){
				temp = 0;
				optionsMenu.setSoundVolume(0);
			}
			settings.at(3)->setString(std::to_string(temp));
		}
		else if (optionsMenu.button.at(3)->clicked)
		{
			optionsMenu.adjustSoundVolume(1);
			int temp = optionsMenu.getSoundVolume();
			if (temp > 100)
			{
				temp = 100;
				optionsMenu.setSoundVolume(100);
			}
			settings.at(3)->setString(std::to_string(temp));
		}
		else if (optionsMenu.button.at(4)->clicked)
		{
			currentGameState = Game::MAIN_MENU;
		}
		break;
	case Game::EXTRAS:
		extrasMenu.update(cursor);

		if (extrasMenu.button.at(0)->clicked)
		{
			currentGameState = Game::HELP;

		}
		else if (extrasMenu.button.at(1)->clicked)
		{
			currentGameState = Game::CREDITS;
		}
		else if (extrasMenu.button.at(2)->clicked)
		{
			currentGameState = Game::MAIN_MENU;
		}
		break;
	case Game::GAME_WIN:
		menuMusic.stopPlay();
		winMov.update();
		if (winMov.movie->getStatus() == 0)
		{
			currentGameState = GameStates::MAIN_MENU;
			menuMusic.playLoop();
		}
		break;
	case Game::GAME_LOSE:
		menuMusic.stopPlay();
		loseMov.update();
		if (loseMov.movie->getStatus() == 0)
		{
			currentGameState = GameStates::MAIN_MENU;
			menuMusic.playLoop();
		}
		break;
	case Game::HELP:
		helpScreen.update();
		if (cursor->ctrlButtons.at(1))
		{
			currentGameState = GameStates::EXTRAS;
		}
		break;
	case Game::CREDITS:
		credits.at(temp).update();
		timeSinceLastUpdate += m_clock.restart();
		myTime += timeSinceLastUpdate.asSeconds();
		if (myTime >= 4)
		{
			temp++;
			if (temp > 2)
			{
				currentGameState = EXTRAS;
				temp = 0;
			}
			myTime = 0;
		}
		timeSinceLastUpdate = sf::Time::Zero;
		break;
	case Game::PAUSE:
		pauseMenu.update(cursor);
		if (pauseMenu.button.at(0)->clicked)
		{
			currentGameState = Game::INGAME;
		}
		else if (pauseMenu.button.at(1)->clicked)
		{
			currentGameState = Game::MAIN_MENU;
			game->theBigReset();
		}
		break;
	default:
		break;
	}
	
}

void Game::render()
{
	window.clear();
	
	switch (currentGameState)
	{
	case Game::SPLASH:
		splashScreen.render(window);
		break;
	case Game::LICENSE:
		licenseScreen.render(window);
		break;
	case Game::MAIN_MENU:
		mainMenu.render(window);
		break;
	case Game::MODE_SELECT:
		playModeMenu.render(window);
		break;
	case Game::INGAME_CUTSCENE:
		moviePlayer.render(window);
		break;
	case Game::INGAME:
		inGameMenu.render(window);
		game->render(window);
		break;
	case Game::OPTIONS:
		optionsMenu.render(window);
		for (int i = 0; i < 4; i++)
		{
			settings.at(i)->render(window);
		}
		
		break;
	case Game::EXTRAS:
		extrasMenu.render(window);
		break;
	case Game::GAME_WIN:
		winMov.render(window);
		break;
	case Game::GAME_LOSE:
		loseMov.render(window);
		break;
	case Game::PAUSE:
		pauseMenu.render(window);
		break;
	case Game::HELP:
		helpScreen.render(window);
		break;
	case Game::CREDITS:
		credits.at(temp).render(window);
		break;
	default:
		break;
	}
	cursor->render(window);
	window.display();
}


