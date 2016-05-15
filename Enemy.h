#pragma once
#include <SFML\Graphics.hpp>
#include "Character.h"
class Enemy : public Character
{
public:
	Enemy();
	void changeDirection(int targetI, int targetJ, int enemyI, int enemyJ);
	void changeHorizontalDirection(int targetJ, int enemyJ);
	void changeVerticalDirection(int targetI, int enemyJ);
	void update(sf::Clock clock);

private:
	sf::Vector2i m_target;

};
