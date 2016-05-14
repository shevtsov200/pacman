#pragma once
#include <SFML\Graphics.hpp>
#include "GameConstants.h"
#include "Character.h"

class Pacman : public Character
{
public: 
	enum directionStates { RIGHT, LEFT, UP, DOWN, NOWHERE};

	Pacman();
	void changeDirection();
	void update(sf::Clock clock);

	//!!!!!!!!
	directionStates m_movingState;

	bool m_testMovingUp;
	bool m_testMovingDown;
	bool m_testMovingRight;
	bool m_testMovingLeft;
	//!!!!!!!!


};
