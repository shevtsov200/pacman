#pragma once
#include <SFML\Graphics.hpp>
#include "GameConstants.h"
#include "Character.h"

class Pacman : public Character
{
public: 
	Pacman();
	void changeDirection();
	void update(sf::Clock clock);
	void die();
	void respawn();
	void playAnimation(sf::Clock clock);
	bool playDeathAnimation(sf::Clock clock);
private:
	bool isAlive;
};
