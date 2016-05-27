#pragma once
#include <SFML\Graphics.hpp>
#include "Character.h"
class Enemy : public Character
{
public:
	Enemy();
	void changeDirection();
	void changeHorizontalDirection();
	void changeVerticalDirection();
	void update(sf::Clock clock);
	void update();

	void setTarget(sf::Vector2i target);

	sf::Vector2i getTarget();
private:
	sf::Vector2i m_target;	
};
