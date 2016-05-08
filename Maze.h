#pragma once
#include <SFML\Graphics.hpp>
#include "GameConstants.h"
#include "Food.h"
class Maze : public sf::Drawable, sf::Transformable
{
public:
	Maze();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void buildWallMatrix(sf::RectangleShape *walls, Food *food, int dim1, int dim2);
	bool getFirstElement();
	void update();
	bool isItWall(int i, int j);
private:
	
	enum tile{SPACE, FOOD, WALL};
	tile tiles[GameConstants::MAZE_HEIGHT][GameConstants::MAZE_WIDTH];

	sf::Sprite mazeSprite;
	sf::Texture spriteSheet;

	//sf::RectangleShape walls[MAZE_HEIGHT][MAZE_WIDTH];
};