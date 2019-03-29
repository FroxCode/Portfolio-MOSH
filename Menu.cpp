//Created by Dale Sinnott
//Multiple layout menu system
#include "Menu.h"
#include <string>
#include <iostream>
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>


Menu::Menu(int btnAmount, std::string labelText, std::string fontTxt, std::string backgroundImg, std::string buttonImg, std::string buttonSnd, float w, float h, std::string btnText[], Vector2f position[], float charSizeBtn, float charSizeHeader) :
m_background(backgroundImg, w, h, 100, 100, true),
m_header(fontTxt, labelText, Vector2f(w / 2, h / 100 * 15), charSizeHeader),
m_buttonAmount(btnAmount)
{
	for (int i = 0; i < btnAmount; i++)
	{
		std::shared_ptr<Button> tempBtn = std::make_shared<Button>(btnText[i], position[i], fontTxt, buttonImg, buttonSnd, w, h, charSizeBtn, true);
		button.push_back(tempBtn);
	}
}
Menu::Menu()
{

}
Menu::~Menu(){}

void Menu::reCreate(int btnAmount, std::string labelText, std::string fontTxt, std::string backgroundImg, std::string buttonImg, std::string buttonSnd, float w, float h, std::string btnText[], Vector2f position[], float charSizeBtn, float charSizeHeader, bool scaleButtonDown)
{ //basically a constructor for if the menu was made with a default constructor
	m_background.reCreate(backgroundImg, w, h, 100, 100, true);
	m_header.reCreate(fontTxt, labelText, Vector2f(w / 2, h / 100 * 15), charSizeHeader);
	m_buttonAmount = btnAmount;
	for (int i = 0; i < m_buttonAmount; i++)
	{
		std::shared_ptr<Button> tempBtn = std::make_shared<Button>(btnText[i], position[i], fontTxt, buttonImg, buttonSnd, w, h, charSizeBtn, scaleButtonDown);
		button.push_back(tempBtn);
	}
}
void Menu::update(shared_ptr<Cursor> &cursor){
	controls(cursor);

	for (int i = 0; i < m_buttonAmount; i++)
	{
		button.at(i)->update();
	}
	m_header.update();

}

void Menu::render(RenderWindow & window){
	//draw object
	m_background.render(window);
	for (int i = 0; i < m_buttonAmount; i++)
	{
		button.at(i)->render(window);
	}
	m_header.render(window);
	
}
void Menu::controls(shared_ptr<Cursor> &cursor)
{ 
	for (int i = 0; i < m_buttonAmount; i++)
	{
		if (button.at(i)->getGlobalBounds().contains(Vector2i(cursor->m_position)))
		{
			if (button.at(i)->currentState == Button::HELD && !cursor->thisA)
			{
				button.at(i)->currentState = Button::RELEASED;
			}
			if (button.at(i)->currentState != Button::RELEASED)
			{
				button.at(i)->currentState = Button::HIGHLIGHTED;
			}
			if (cursor->thisA)
			{
				button.at(i)->currentState = Button::HELD;
			}
		}
		else
		{
			button.at(i)->currentState = Button::UNSELECTED;
		}
	}
	

	
}
void Menu::setSoundVolume(int vol)
{//change the volume of buttons depending on layout
	
	for (int i = 0; i < m_buttonAmount; i++)
	{
		button.at(i)->setVolume(vol);
	}
	
}
void Menu::adjustSoundVolume(int vol)
{//change the volume of buttons depending on layout

	for (int i = 0; i < m_buttonAmount; i++)
	{
		button.at(i)->adjustVolume(vol);
	}

}
int Menu::getSoundVolume()
{ //get sound volume from 1 button as they are all the same
	return static_cast<int>(button.at(0)->clickSound.getVolume());
}