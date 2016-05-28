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
	IntMatrix &getMazeVector();
	void update();
	bool isItWall(sf::Vector2i wallPosition) const;
private:
	IntMatrix m_tiles;

	sf::Sprite m_mazeSprite;
	sf::Texture m_spriteSheet;
};