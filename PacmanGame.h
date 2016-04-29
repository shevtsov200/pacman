#pragma once
#include <SFML\Graphics.hpp>
#include "Pacman.h"
class PacmanGame
{
public:
	PacmanGame();
	//~PacmanGame();
	void processEvent(sf::Event event);
	void update(sf::Clock clock);
	void draw(sf::RenderTarget & target);
private:
	Pacman m_pacman;

};