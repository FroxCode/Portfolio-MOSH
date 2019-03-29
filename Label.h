////////////////////////////////////////////////////////////
//
// Created by Dale
//
////////////////////////////////////////////////////////////
#ifndef _LABEL_H_
#define _LABEL_H_
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
using namespace sf;
class Label
{
public:
	////////////////////////////////////////////////////////////
	/// Overloaded constructor
	///
	////////////////////////////////////////////////////////////
	Label(std::string font, std::string text, Vector2f position, float charSize);

	////////////////////////////////////////////////////////////
	/// Default constructor
	///
	////////////////////////////////////////////////////////////
	Label();

	////////////////////////////////////////////////////////////
	/// Default constructor
	///
	////////////////////////////////////////////////////////////
	~Label();

	////////////////////////////////////////////////////////////
	/// Creates a new label
	///
	////////////////////////////////////////////////////////////
	void reCreate(std::string font, std::string text, Vector2f position, float charSize);

	////////////////////////////////////////////////////////////
	/// updates the labels
	///
	////////////////////////////////////////////////////////////
	void update();

	////////////////////////////////////////////////////////////
	/// renders the labels in the game window
	///
	////////////////////////////////////////////////////////////
	void render(sf::RenderWindow &window);
	////////////////////////////////////////////////////////////
	/// sets the text inside the label
	///
	////////////////////////////////////////////////////////////
	void setString(std::string str); 
	std::string getString();
private:
	sf::Font m_font;
	sf::Text m_text;
	sf::Vector2f m_position;
	
};
#endif
