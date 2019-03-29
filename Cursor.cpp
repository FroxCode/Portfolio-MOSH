#include "Cursor.h"
#include <iostream>
Cursor::Cursor(){}
Cursor::~Cursor(){}

Cursor::Cursor(Vector2f position, string const &texture) :
m_position(position)
{
	//load textures
	if (!m_texture.loadFromFile(texture))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	if (!m_crosshair.loadFromFile("assets/crosshairs.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	for (int i = 0; i < TOTAL_BUTTONS; i++)
	{ //make new bool for each button
		bool tempBtn = false;
		ctrlButtons.push_back(false);
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
}
void Cursor::update()
{
	
	for (int i = 0; i < TOTAL_BUTTONS; i++)
	{
		ctrlButtons.at(i) = false; //reset all buttons to false
	}
	controls(); //check controller


	//If any of these buttons have been pressed and released, set their bool to true
	if (lastA && !thisA){ ctrlButtons.at(0) = true; } 
	else if (lastB && !thisB){ ctrlButtons.at(1) = true; }
	else if (lastX && !thisX){ ctrlButtons.at(2) = true; }
	else if (lastY && !thisY){ ctrlButtons.at(3) = true; }
	else if (lastLB && !thisLB){ ctrlButtons.at(4) = true; }
	else if (lastRB && !thisRB){ ctrlButtons.at(5) = true; }
	else if (lastBack && !thisBack){ ctrlButtons.at(6) = true; }
	else if (lastStart && !thisStart){ ctrlButtons.at(7) = true; }
	else if (lastRStick && !thisRStick){ ctrlButtons.at(8) = true; }


	m_sprite.setPosition(m_position);

	if (crosshair && m_sprite.getTexture() != &m_crosshair)
	{//change to crosshair 
		m_sprite.setTexture(m_crosshair);
	}
	else if (!crosshair && m_sprite.getTexture() != &m_texture)
	{ //change to pointer
		m_sprite.setTexture(m_texture);
	}
}
void Cursor::render(RenderWindow &window)
{
	if (!window.getViewport(window.getView()).contains(Vector2i(m_position)))
	{
		m_position = Vector2f(640,360); //move the cursor back to center if it leaves the border
	}
	window.draw(m_sprite);
	
}
void Cursor::controls()
{
	//set last states
	lastDpadX = thisDpadX;
	lastDpadY = thisDpadY;
	lastA = thisA;
	lastB = thisB;
	lastX = thisX;
	lastY = thisY;
	lastLB = thisLB;
	lastRB = thisRB;
	lastRStick = thisRStick;
	lastBack = thisBack;
	lastStart = thisStart;
	lastDpadX = thisDpadX;
	lastDpadY = thisDpadY;
	directionPad = 0;
	thisLStickX = 0;
	thisLStickY = 0;
	//set new states
	//Buttons
	if (Joystick::isButtonPressed(0, 0)){ thisA = true; } //A
	else{ thisA = false; }

	if (Joystick::isButtonPressed(0, 1)){ thisB = true; } //B
	else{ thisB = false; }

	if (Joystick::isButtonPressed(0, 2)){ thisX = true; } //X
	else{ thisX = false; }

	if (Joystick::isButtonPressed(0, 3)){ thisY = true; } //Y
	else{ thisY = false; }

	if (Joystick::isButtonPressed(0, 4)){ thisLB = true; } //Left Bumper
	else{ thisLB = false; }

	if (Joystick::isButtonPressed(0, 5)){ thisRB = true; } //Right Bumper
	else{ thisRB = false; }

	if (Joystick::isButtonPressed(0, 6)){ thisBack = true; } //Back
	else{ thisBack = false; }

	if (Joystick::isButtonPressed(0, 7)){ thisStart = true; } //Start
	else{ thisStart = false; }

	if (Joystick::isButtonPressed(0, 9)){ thisRStick = true; } //Right Stick In
	else{ thisRStick = false; }
	//Left Stick
	
	if (Joystick::getAxisPosition(0, sf::Joystick::Axis::X) >= 18.f || Joystick::getAxisPosition(0, sf::Joystick::Axis::X) <= -18.f)
	{//deadzoning
		thisLStickX = Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
	}
	if (Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) >= 18.f || Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) <= -18.f)
	{//deadzoning
		thisLStickY = Joystick::getAxisPosition(0, sf::Joystick::Axis::Y);
	}
	

	m_position.x += thisLStickX * m_speed;
	m_position.y += thisLStickY * m_speed;

	//Dpad controls
	thisDpadY = Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY);
	thisDpadX = Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX);


	if (thisDpadY == 100 && lastDpadY == 0){ directionPad = 2; }//down
	else if (thisDpadY == -100 && lastDpadY == 0){ directionPad = 1; }//up
	if (thisDpadX == 100 && lastDpadX == 0) { directionPad = 4; } //right
	else if (thisDpadX == -100 && lastDpadX == 0){ directionPad = 3; }//left
}