#pragma once
#include <SFML\Graphics.hpp>
#include "Pacman.h"
#include "Maze.h"
class PacmanGame
{
public:
	PacmanGame();
	void processEvent(sf::Event event);
	void update(sf::Clock clock);
	void draw(sf::RenderTarget & target);
	void resolveCollision();
private:
	Maze m_maze;
	Pacman m_pacman;

	const static int MAZE_WIDTH = 28;
	const static int MAZE_HEIGHT = 31;
	

};