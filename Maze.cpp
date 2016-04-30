#include "Maze.h"
#include <SFML\Graphics.hpp>
Maze::Maze()
{
	for (int i = 0; i < MAZE_WIDTH; i++)
	{
		for (int j = 0; j < MAZE_HEIGHT; j++)
		{
			isWall[i][j] = false;
		}
	}

	isWall[5][5] = true;

	spriteSheet.loadFromFile("spriteSheet2.png");
	wallSprite.setTexture(spriteSheet);
	wallSprite.setTextureRect(sf::IntRect(228, 0,223, 247));
	wallSprite.setScale(3,3);
	
	wallSprite.setColor(sf::Color::White);
}

void Maze::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < MAZE_WIDTH; i++)
	{
		for (int j = 0; j < MAZE_HEIGHT; j++)
		{
			if (isWall[i][j])
			{
				target.draw(wallSprite, states);
			}
		}
	}
}

void Maze::update()
{
	for (int i = 0; i < MAZE_WIDTH; i++)
	{
		for (int j = 0; j < MAZE_HEIGHT; j++)
		{
			if (isWall[i][j])
			{
				wallSprite.setPosition(0, 0);
			}
		}
	}
}
