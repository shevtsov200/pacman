#pragma once
#include <SFML\Graphics.hpp>
#include "GameConstants.h"
#include "Pacman.h"
#include "Maze.h"
class PacmanGame
{
public:
	PacmanGame();
	void processEvent(sf::Event event);
	void update(sf::Clock clock);
	void draw(sf::RenderTarget & target);
	void debugDraw(sf::RenderTarget & target) const;
	bool resolveCollision();
private:


	Maze m_maze;
	Pacman m_pacman;
	sf::RectangleShape m_walls[GameConstants::MAZE_HEIGHT][GameConstants::MAZE_WIDTH];
	

};