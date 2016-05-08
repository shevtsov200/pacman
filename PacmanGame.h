#pragma once
#include <vector>
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
	sf::Texture spriteSheet;
	sf::Texture pacmanSpriteSheet;
	Maze m_maze;
	Pacman m_pacman;
	sf::RectangleShape m_walls[GameConstants::MAZE_HEIGHT][GameConstants::MAZE_WIDTH];
	std::vector<Food> m_food;


	sf::RectangleShape debugCurrentTile;
};