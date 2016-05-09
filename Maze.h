#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "GameConstants.h"
#include "Food.h"
class Maze : public sf::Drawable, sf::Transformable
{
public:
	Maze();
	void setTexture(sf::Texture &spriteSheet);
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void buildWallMatrix(sf::RectangleShape *walls, std::vector<Food> &food, int dim1, int dim2);
	bool getFirstElement();
	void update();
	bool isItWall(int i, int j);
private:
	
	enum tile{SPACE, FOOD, WALL};
	tile m_tiles[GameConstants::MAZE_HEIGHT][GameConstants::MAZE_WIDTH];

	sf::Sprite m_mazeSprite;
	sf::Texture m_spriteSheet;
};