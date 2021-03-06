////////////////////////////////////////////////////////////
//
// Created by Dale
//
////////////////////////////////////////////////////////////
#ifndef MOVIEPLAYER_H
#define MOVIEPLAYER_H
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML\Graphics.hpp>
#include <SFML/Config.hpp>
#include <sfeMovie\include\Movie.hpp>
#include <iostream>
#include <algorithm>
#include <memory>
using namespace std;
using namespace sf;
class MoviePlayer
{
public:
	////////////////////////////////////////////////////////////
	/// Default constructor
	///
	////////////////////////////////////////////////////////////
	MoviePlayer();

	////////////////////////////////////////////////////////////
	/// overloaded constructor
	///
	////////////////////////////////////////////////////////////
	MoviePlayer(std::string movieFile);

	////////////////////////////////////////////////////////////
	/// default constructor
	///
	////////////////////////////////////////////////////////////
	~MoviePlayer();

	////////////////////////////////////////////////////////////
	/// renders the movie clips
	///
	////////////////////////////////////////////////////////////
	void render(RenderWindow &window);

	////////////////////////////////////////////////////////////
	/// update sthe movie clips
	///
	////////////////////////////////////////////////////////////
	void update();

	////////////////////////////////////////////////////////////
	/// plays the movie clips
	///
	////////////////////////////////////////////////////////////
	void play();
	shared_ptr<sfe::Movie> movie;
	bool isPlaying = false;
private:


};



#endif;