////////////////////////////////////////////////////////////
//
// Created by Connor
//
////////////////////////////////////////////////////////////
#ifndef GAMEDATA_H_
#define GAMEDATA_H_
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <string>
#include <SFML\Graphics.hpp>
using namespace std;
class GameData 
{

public:
	
	////////////////////////////////////////////////////////////
	/// Contains all the variables that will store values from 
	//  the GameData file. 
	///
	////////////////////////////////////////////////////////////
	//HUD
	int tokens[10];
	int credits[10];

	//Positions
	int portalPositionX;
	int portalPositionY;
	int basePositionX;
	int basePositionY;

	//Enemies per wave
	int flyingNum[10];
	int walkingNum[10];
	int mountedNum[10];

	//Overlays
	string splashImage;
	string menuImage;
	string creditsImageOne;
	string creditsImageTwo;
	string creditsImageThree;

	//Sprites
	string portalImage;
	string baseImage;

	//Headings

	string menuHeading;
	string extrasHeading;
	string modeHeading;
	string optionsHeading;
	string pauseHeading;

	//Game
	int screenWidth;
	int screenHeight;

	//Font 
	string font;

	//Buttons
	string menuButtonImage;
	string towerButtonImage;
	string pauseButtonImage;
	string buttonSounds;

	//Music
	string gameMusic;
};
#endif;