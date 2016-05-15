#pragma once
#include <vector>
#include <iostream>
#include <SFML\Graphics.hpp>
#include "GameConstants.h"
#include "Food.h"
class Maze : public sf::Drawable, sf::Transformable
{
public:
	enum tile { SPACE, FOOD, WALL };
	Maze();
	void setTexture(sf::Texture &spriteSheet);
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void buildMapMatrix(int dim1, int dim2, std::string mapName);
	void placeWalls(sf::RectangleShape *walls, int dim1, int dim2);
	void placeFood(std::vector<Food> &food, int dim1, int dim2);
	bool getFirstElement();
	void update();
	bool isItWall(int i, int j);
private:
	
	
	tile m_tiles[GameConstants::MAZE_HEIGHT][GameConstants::MAZE_WIDTH];

	sf::Sprite m_mazeSprite;
	sf::Texture m_spriteSheet;
};