#pragma once
#include <SFML\Graphics.hpp>
#include "Character.h"
class Enemy : public Character
{
public:
	enum directionStates { RIGHT, LEFT, UP, DOWN, NOWHERE };

	Enemy();
	void changeDirection(int targetI, int targetJ, int enemyI, int enemyJ);
	void changeHorizontalDirection(int targetJ, int enemyJ);
	void changeVerticalDirection(int targetI, int enemyJ);
	void update(sf::Clock clock);

	//!!!!!!!!
	directionStates m_movingState;

	bool m_testMovingUp;
	bool m_testMovingDown;
	bool m_testMovingRight;
	bool m_testMovingLeft;
	//!!!!!!!!

private:
	sf::Vector2i m_target;

};
