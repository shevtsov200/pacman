#pragma once
#include <SFML\Graphics.hpp>
#include "GameConstants.h"
class Maze : public sf::Drawable, sf::Transformable
{
public:
	Maze();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void buildWallMatrix(sf::RectangleShape *walls, int dim1, int dim2);
	bool getFirstElement();
	void update();
	bool isItWall(int i, int j);
private:
	
	bool isWall[GameConstants::MAZE_HEIGHT][GameConstants::MAZE_WIDTH];

	sf::Sprite mazeSprite;
	sf::Texture spriteSheet;

	//sf::RectangleShape walls[MAZE_HEIGHT][MAZE_WIDTH];
};