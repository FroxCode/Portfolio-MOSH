//Created by Dale Sinnott
#include "MoviePlayer.h"


MoviePlayer::MoviePlayer(){}
MoviePlayer::~MoviePlayer(){}

MoviePlayer::MoviePlayer(std::string movieFile)
{
	movie = make_shared<sfe::Movie>();
	if (!movie->openFromFile(movieFile)) //load movie
	{
		cout << movieFile << " not loaded" << endl;
	}
	movie->fit(0, 0, 1280, 720); //fit to screen
	
}
void MoviePlayer::render(RenderWindow &window)
{
	if (isPlaying)
	{
		window.draw(*movie); 
	}
}
void MoviePlayer::update()
{
	movie->update();
	if (movie->getStatus() != sfe::Playing)
	{
		isPlaying = false;
	}
}
void MoviePlayer::play()
{
	movie->play();
	isPlaying = true;
}