#pragma once
#include <SFML\Graphics.hpp>
class Maze : public sf::Drawable, sf::Transformable
{
public:
	Maze();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void buildWallMatrix(sf::RectangleShape *walls, int dim1, int dim2);
	bool getFirstElement();
	void update();
private:
	const static bool IS_DEBUGGING = false;

	const static int SCALE = 3;
	const static int MAZE_WIDTH = 28;
	const static int MAZE_HEIGHT = 31;
	const static int TILE_WIDTH = 8 * SCALE;
	const static int TILE_HEIGHT = TILE_WIDTH;
	bool isWall[MAZE_HEIGHT][MAZE_WIDTH];

	sf::Sprite mazeSprite;
	sf::Texture spriteSheet;

	//sf::RectangleShape walls[MAZE_HEIGHT][MAZE_WIDTH];
};