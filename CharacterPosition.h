#include <SFML\Graphics.hpp>

/*class CharacterPosition
{
public:
	CharacterPosition() : m_pixelPosition(0.0f, 0.0f), m_tilePosition(0, 0) {};
private:
	sf::Vector2f m_pixelPosition;
	sf::Vector2i m_tilePosition;
};*/

/*class CharacterPosition
{
public:
	CharacterPosition();//CharacterPosition() : m_pixelPosition(0, 0), m_tilePosition(0, 0) {};
	CharacterPosition(sf::Vector2f pixelPosition, sf::Vector2i tilePosition);
	//CharacterPosition(sf::Vector2f pixelPosition, sf::Vector2i tilePosition) : m_pixelPosition(pixelPosition), m_tilePosition(tilePosition) {};
	void setPixelPosition(sf::Vector2f pixelPosition);
	void setTilePosition(sf::Vector2i tilePosition);
	sf::Vector2f getPixelPosition() const;
	sf::Vector2i getTilePosition() const;
	//CharacterPosition &operator=(const CharacterPosition& other);
	//CharacterPosition &operator+(const CharacterPosition& other);	
private:
	sf::Vector2f m_pixelPosition;
	sf::Vector2i m_tilePosition;
	
};

CharacterPosition::CharacterPosition() : m_pixelPosition(0, 0), m_tilePosition(0, 0) {};
CharacterPosition::CharacterPosition(sf::Vector2f pixelPosition, sf::Vector2i tilePosition) : m_pixelPosition(pixelPosition), m_tilePosition(tilePosition) {};


void CharacterPosition::setPixelPosition(sf::Vector2f pixelPositon)
{
	m_pixelPosition = pixelPositon;
}
void CharacterPosition::setTilePosition(sf::Vector2i tilePosition)
{
	m_tilePosition = tilePosition;
}
sf::Vector2f CharacterPosition::getPixelPosition() const
{
	return m_pixelPosition;
}
sf::Vector2i CharacterPosition::getTilePosition() const
{
	return m_tilePosition;
}*/
/*CharacterPosition &CharacterPosition::operator=(const CharacterPosition& other)
{
	m_pixelPosition = other.m_pixelPosition;
	m_tilePosition = other.m_tilePosition;
	return *this;

}
CharacterPosition &CharacterPosition::operator+(const CharacterPosition& other)
{
	sf::Vector2f pixelPosition = m_pixelPosition + other.m_pixelPosition;
	sf::Vector2i tilePosition = m_tilePosition + other.m_tilePosition;
	return CharacterPosition(pixelPosition, tilePosition);
}*/
