//Created by Dale Sinnott
#include "Overlay.h"
#include <string>

Overlay::Overlay(std::string imageName, float w, float h, float xPer, float yPer, bool centered)
{
	//load files
	if (!background_texture.loadFromFile(imageName))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}

	background_texture.setSmooth(true); //smoothen  image
	background_sprite.setTexture(background_texture); //apply image to sprite
	background_sprite.setPosition(0, 0); //default position
	background_sprite.setColor(sf::Color(255, 255, 255, 0)); //make invisible

	//scale the image to the percentage of screen
	background_sprite.setScale(((w / 100.0f) * xPer) / background_sprite.getLocalBounds().width, 
		((h / 100.0f) * yPer) / background_sprite.getLocalBounds().height);

	//if the image is to be centered, then move the sprite to the appropriate position based upon its scale
	if (centered)
	{
		background_sprite.setPosition((w / 2) - ((background_sprite.getScale().x * background_texture.getSize().x) / 2), (h / 2) - (background_sprite.getScale().y * background_texture.getSize().y / 2));
	}
}
Overlay::Overlay(std::string imageName, float w, float h, float xPer, float yPer, Vector2f position)
{//same as last constructor except for the custom position assignment and no center option
	if (!background_texture.loadFromFile(imageName))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	background_texture.setSmooth(true);
	background_sprite.setTexture(background_texture);
	background_sprite.setPosition(0, 0);
	background_sprite.setColor(sf::Color(255, 255, 255, 0));
	background_sprite.setScale(((w / 100.0f) * xPer) / background_sprite.getLocalBounds().width, ((h / 100.0f) * yPer) / background_sprite.getLocalBounds().height);
	background_sprite.setPosition(position.x - (background_sprite.getLocalBounds().width / 2.0f), position.y);
}
Overlay::Overlay()
{

}


void Overlay::update(){
	//empty
}
void Overlay::render(RenderWindow & window){
	window.draw(background_sprite); //draw sprite
}
void Overlay::fadeIn(){
	//fade in animation
	count += 1;
		background_sprite.setColor(sf::Color(255, 255, 255, count * 4.25));

}
void Overlay::fadeOut(){
	//fade in animation
	num += 1;
		background_sprite.setColor(sf::Color(255, 255, 255, 255 - (num * 4.25)));
		
}
void Overlay::centerOrigin(){
	//move the origin to the center of the sprite
	background_sprite.setPosition(background_sprite.getPosition().x + background_sprite.getLocalBounds().width / 1.20 , background_sprite.getPosition().y + background_sprite.getLocalBounds().height / 1.20);
	background_sprite.setOrigin(background_sprite.getLocalBounds().width / 2, background_sprite.getLocalBounds().height / 2);
}
void Overlay::rotate(float angle){
	background_sprite.rotate(angle);
}
void Overlay::reCreate(std::string imageName, float w, float h, float xPer, float yPer, bool centered)
{
	if (!background_texture.loadFromFile(imageName))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}

	background_texture.setSmooth(true); //smoothen  image
	background_sprite.setTexture(background_texture); //apply image to sprite
	background_sprite.setPosition(0, 0); //default position
	background_sprite.setColor(sf::Color(255, 255, 255, 255)); 

	//scale the image to the percentage of screen
	background_sprite.setScale(((w / 100.0f) * xPer) / background_sprite.getLocalBounds().width,
		((h / 100.0f) * yPer) / background_sprite.getLocalBounds().height);

	//if the image is to be centered, then move the sprite to the appropriate position based upon its scale
	if (centered)
	{
		background_sprite.setPosition((w / 2) - ((background_sprite.getScale().x * background_texture.getSize().x) / 2), (h / 2) - (background_sprite.getScale().y * background_texture.getSize().y / 2));
	}
}
void Overlay::reCreate(std::string imageName, float w, float h, float xPer, float yPer, Vector2f position)
{
	if (!background_texture.loadFromFile(imageName))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	background_texture.setSmooth(true);
	background_sprite.setTexture(background_texture);
	background_sprite.setPosition(0, 0);
	background_sprite.setColor(sf::Color(255, 255, 255, 255));
	background_sprite.setScale(((w / 100.0f) * xPer) / background_sprite.getLocalBounds().width, ((h / 100.0f) * yPer) / background_sprite.getLocalBounds().height);
	background_sprite.setPosition(position.x - (background_sprite.getLocalBounds().width / 2.0f), position.y);
}
void Overlay::reCreate(std::string imageName, Vector2f position)
{
	if (!background_texture.loadFromFile(imageName))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	background_texture.setSmooth(true);
	background_sprite.setTexture(background_texture);
	background_sprite.setColor(sf::Color(255, 255, 255, 255));
	background_sprite.setPosition(position.x , position.y);
}