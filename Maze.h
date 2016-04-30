#pragma once
#include <SFML\Graphics.hpp>
class Maze : public sf::Drawable, sf::Transformable
{
public:
	Maze();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void update();
private:
	const static int MAZE_WIDTH = 15;
	const static int MAZE_HEIGHT = 15;
	const static int TILE_WIDTH = 8;
	const static int TILE_HEIGHT = TILE_WIDTH;
	bool isWall[MAZE_WIDTH][MAZE_HEIGHT];

	sf::Sprite wallSprite;
	sf::Texture spriteSheet;
};