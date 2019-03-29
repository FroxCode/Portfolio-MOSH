//////////////////////////////////////////////////////////////
//
// Created by Dale
//
////////////////////////////////////////////////////////////
#ifndef CURSOR_H
#define CURSOR_H
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML\Graphics.hpp>
#include <memory>
using namespace std;
using namespace sf;
class Cursor{
public:
	////////////////////////////////////////////////////////////
	/// Default constructor
	///
	////////////////////////////////////////////////////////////
	Cursor();

	////////////////////////////////////////////////////////////
	/// Default destructor
	///
	////////////////////////////////////////////////////////////
	~Cursor();

	////////////////////////////////////////////////////////////
	/// Overloaded constructor
	///
	////////////////////////////////////////////////////////////
	Cursor(sf::Vector2f position, string const &texture);

	////////////////////////////////////////////////////////////
	/// Updates the cursor object
	///
	////////////////////////////////////////////////////////////
	void update();

	////////////////////////////////////////////////////////////
	/// Draws the object
	///
	////////////////////////////////////////////////////////////
	void render(RenderWindow &window);

	Vector2f m_position;
	Texture m_texture;
	Texture m_crosshair;
	Sprite m_sprite;
	float m_speed = 0.2f;
	vector<bool> ctrlButtons;

	bool crosshair = false;
	bool thisA = false;
private:
	int const TOTAL_BUTTONS = 9;
	void controls();
	
	bool lastA = false;
	bool thisB = false;
	bool lastB = false;
	bool thisX = false;
	bool lastX = false;
	bool thisY = false;
	bool lastY = false;
	bool thisLB = false;
	bool lastLB = false;
	bool thisRB = false;
	bool lastRB = false;
	bool thisRStick = false;
	bool lastRStick = false;
	bool thisBack = false;
	bool lastBack = false;
	bool thisStart = false;
	bool lastStart = false;
	//direction controls
	float thisLStickX = 0;
	float thisLStickY = 0;

	float thisDpadY = 0;
	float lastDpadY = 0;
	float thisDpadX = 0;
	float lastDpadX = 0;
	int directionPad = 0; //0 nothing, 1 up, 2 down, 3 left, 4 right
};
#endif