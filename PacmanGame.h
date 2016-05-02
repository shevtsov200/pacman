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
	void debugDraw(sf::RenderTarget & target) const;
	void resolveCollision();
private:
	const static bool IS_DEBUGGING = false;
	const static int MAZE_WIDTH = 28;
	const static int MAZE_HEIGHT = 31;

	Maze m_maze;
	Pacman m_pacman;
	sf::RectangleShape m_walls[MAZE_HEIGHT][MAZE_WIDTH];
	

};