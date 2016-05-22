#pragma once
#include <SFML\Graphics.hpp>
#include "Character.h"
#include "CharacterPosition.h"
class Enemy : public Character
{
public:
	Enemy();
	void findPath();
	void changeDirection();
	//void changeDirection();
	void changeHorizontalDirection();
	void changeVerticalDirection();
	void update(sf::Clock clock);
	void update();

	void setTarget(sf::Vector2i target);

	sf::Vector2i getTarget();
private:
	sf::Vector2i m_target;
	//int m_lastCharacterI, m_lastCharacterJ;
	
};
