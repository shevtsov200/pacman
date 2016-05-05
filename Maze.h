#pragma once
#include <SFML\Graphics.hpp>
#include "PacmanGame.h"
#include "Pacman.h"
class Maze : public sf::Drawable, sf::Transformable
{
public:
	Maze(const PacmanGame* game);
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void Maze::debugDraw(sf::RenderTarget & target) const;
	void buildWallMatrix(sf::RectangleShape *walls, int dim1, int dim2);
	bool getFirstElement();
	void update();

	const int getScale();
	const int getTileSize();
	const int getSheetTileSize();
	const bool getIsDebugging();
private:
	const static int MAZE_WIDTH = 28;
	const static int MAZE_HEIGHT = 31;

	int tileSize;
	int mazeWidth;
	int mazeHeight;
	int scale;
	bool isDebugging;

	bool isWall[MAZE_HEIGHT][MAZE_WIDTH];
	sf::RectangleShape m_walls[MAZE_HEIGHT][MAZE_WIDTH];

	const PacmanGame *m_game;
	Pacman m_pacman;

	sf::Sprite mazeSprite;
	sf::Texture spriteSheet;

	//sf::RectangleShape walls[MAZE_HEIGHT][MAZE_WIDTH];
};