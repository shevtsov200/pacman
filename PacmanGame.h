#pragma once
#include <SFML\Graphics.hpp>
#include "Maze.h"
#include "Pacman.h"
class PacmanGame
{
public:
	PacmanGame();
	void processEvent(sf::Event event);
	void update(sf::Clock clock);
	void draw(sf::RenderTarget & target);
	bool resolveCollision();
	sf::Vector2<int> pixelsToIndex(sf::Vector2f point);

	const int getScale();
	const int getSheetTileSize();
	const int getTileSize();
	const bool getIsDebugging();
private:
	const static bool IS_DEBUGGING = true;

	const static int SCALE = 3;

	const static int SHEET_TILE_SIZE = 8;
	const static int TILE_SIZE = SHEET_TILE_SIZE*SCALE;

	Maze m_maze;
	Pacman m_pacman;
	

};