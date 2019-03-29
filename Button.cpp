//Created by Dale Sinnott
#include "Button.h"

Button::Button(std::string txt, sf::Vector2f position, std::string font, std::string buttonImg, std::string buttonSnd, float width, float height, float charSize, bool scaleDown) :
m_position(position),
m_scaleDown(scaleDown)
{
	//load files
	if (!buffer.loadFromFile(buttonSnd))
	{
		std::string s("Error loading sound");
		throw std::exception(s.c_str());
	}
	if (!btnTexture.loadFromFile(buttonImg))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	if (!m_font.loadFromFile(font))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}

	m_width = width; //window dimensions
	m_height = height;
	

	

	btnTexture.setSmooth(true); //smooths edges of texture to help with pixelation due to scaling
	btnSprite.setTexture(btnTexture); //assign texture to sprite
	btnSprite.setPosition(m_position.x - (btnTexture.getSize().x / 4), m_position.y - (btnTexture.getSize().y / 4)); 
	btnSprite.setColor(sf::Color(255, 255, 255, 0)); //set to transparent


	m_position_unchanged = btnSprite.getPosition(); //default position for resetting

	m_text.setFont(m_font);
	m_text.setString(txt);
	m_text.setCharacterSize(charSize);
	m_text.setPosition(btnSprite.getPosition()); //move the text to the buttons position

	buffer.loadFromFile(buttonSnd); //load click sound
	clickSound.setBuffer(buffer); //assign the buffer to the sound effect
	clickSound.setVolume(50); //max volume
	if (m_scaleDown)
	{
		btnSprite.setScale(0.5f, 0.5f); //scale down
	}
}
Button::Button()
{

}
Button::~Button(){}

void Button::update()
{//Checks state of button
	clicked = false; 

	btnSprite.setPosition(m_position_unchanged);
	if (currentState == Button::HIGHLIGHTED)
	{//apply effect when highlighted
		btnSprite.setPosition(btnSprite.getPosition().x + 2, btnSprite.getPosition().y + 2);
		btnSprite.setColor(sf::Color::Yellow);
		lastState = currentState;		
	}
	else if (currentState == Button::HELD)
	{ //more drastic effect when held down
		btnSprite.setPosition(btnSprite.getPosition().x + 4, btnSprite.getPosition().y + 4);
		btnSprite.setColor(sf::Color::Green);
		lastState = currentState;
	}
	else if (currentState == Button::RELEASED)
	{//return the button to normal when released  and set clicked to true
		btnSprite.setColor(sf::Color::White);
		lastState = Button::RELEASED;
		currentState = Button::HIGHLIGHTED;
		clickSound.play();
		clicked = true;
	}
	else if (currentState == Button::UNSELECTED)
	{//default state
		btnSprite.setColor(sf::Color::White);
		lastState = currentState;
	}

	//move the text to where the button is, for realistic animation
	if (m_scaleDown)
	{
		m_text.setPosition(btnSprite.getPosition().x + (btnSprite.getLocalBounds().width / 4) - (m_text.getLocalBounds().width / 2), btnSprite.getPosition().y + (btnSprite.getLocalBounds().height / 4) - (m_text.getLocalBounds().height / 2));
	}
	else
	{
		m_text.setPosition(btnSprite.getPosition().x + (btnSprite.getLocalBounds().width / 2) - (m_text.getLocalBounds().width / 2), btnSprite.getPosition().y + (btnSprite.getLocalBounds().height / 1.25) - (m_text.getLocalBounds().height / 2));

	}
}
void Button::render(sf::RenderWindow &window)
{ //draws the button and text
	window.draw(btnSprite);
	window.draw(m_text);
}
void Button::fadeIn()
{ //fade in by 1/60 of 255 per frame
	count += 1;
	btnSprite.setColor(sf::Color(255, 255, 255, count * 4.25));
}
void Button::fadeOut()
{ //fade out by 1/60 of 255 per frame
	num += 1;
	btnSprite.setColor(sf::Color(255, 255, 255, 255 - (num * 4.25)));
}
void Button::setVolume(int vol)
{//set button volume
	clickSound.setVolume(vol);
}
void Button::adjustVolume(int vol)
{//set button volume
	clickSound.setVolume(clickSound.getVolume() + vol);
}
IntRect Button::getGlobalBounds()
{
	return static_cast<IntRect>(btnSprite.getGlobalBounds());
}
Vector2f Button::getPosition()
{
	return m_position;
}
float Button::getWidth()
{
	return btnSprite.getLocalBounds().width;
}
float Button::getHeight()
{
	return btnSprite.getLocalBounds().height;
}