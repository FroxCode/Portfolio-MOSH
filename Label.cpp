//Created by Dale Sinnott
//Simple label
#include "Label.h"

Label::Label(std::string font, std::string text, Vector2f position, float charSize)
{//font, text, position and size of text in pixels

	//load font
	if (!m_font.loadFromFile(font))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}

	//create text and set size/position
	m_text.setFont(m_font);
	m_text.setString(text);
	m_text.setCharacterSize(charSize);
	m_position = position;
	m_text.setPosition(position.x - m_text.getLocalBounds().width / 2, position.y - m_text.getLocalBounds().height / 2);
	m_text.setStyle(Text::Underlined);
}
Label::Label()
{

}
Label::~Label(){}

void Label::update(){
	//always center the text on its assigned position
	m_text.setPosition(m_position.x - m_text.getLocalBounds().width / 2, m_position.y - m_text.getLocalBounds().height / 2);
}
void Label::render(sf::RenderWindow &window){
	window.draw(m_text); //draw text
}
void Label::setString(std::string str)
{
	m_text.setString(str); //change text
}
std::string Label::getString()
{
	return m_text.getString(); //send text
}
void Label::reCreate(std::string font, std::string text, Vector2f position, float charSize)
{
	if (!m_font.loadFromFile(font))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}

	//create text and set size/position
	m_text.setFont(m_font);
	m_text.setString(text);
	m_text.setCharacterSize(charSize);
	m_position = position;
	m_text.setPosition(position.x - m_text.getLocalBounds().width / 2, position.y - m_text.getLocalBounds().height / 2);
	m_text.setStyle(Text::Underlined);
}