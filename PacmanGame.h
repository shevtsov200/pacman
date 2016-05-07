#pragma once
#include <SFML\Graphics.hpp>
#include "GameConstants.h"
#include "Pacman.h"
#include "Maze.h"
#include "Food.h"
class PacmanGame
{
public:
	PacmanGame();
	void processEvent(sf::Event event);
	void update(sf::Clock clock);
	void draw(sf::RenderTarget & target);
	void debugDraw(sf::RenderTarget & target) const;
	int pixelsToIndex(float x);
	void resolveCollision();

private:
	Maze m_maze;
	Pacman m_pacman;
	sf::RectangleShape m_walls[GameConstants::MAZE_HEIGHT][GameConstants::MAZE_WIDTH];
	Food food;
	Food m_food[GameConstants::MAZE_HEIGHT][GameConstants::MAZE_WIDTH];


	sf::RectangleShape debugCurrentTile;
};