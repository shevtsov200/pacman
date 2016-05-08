#include <fstream>
#include <SFML\Graphics.hpp>
#include "Maze.h"

Maze::Maze()
{
	spriteSheet.loadFromFile("spriteSheet2.png");
	mazeSprite.setTexture(spriteSheet);
	mazeSprite.setTextureRect(sf::IntRect(228, 0, 223, 247));
	mazeSprite.setScale(GameConstants::SCALE, GameConstants::SCALE);
}

void Maze::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mazeSprite, states);
}

void Maze::buildWallMatrix(sf::RectangleShape *walls, std::vector<Food> &food, int dim1, int dim2)
{
	std::ifstream mapFile;

	if (GameConstants::IS_DEBUGGING)
	{
		mapFile.open("resources/debugMap.txt");
	}
	else
	{
		mapFile.open("resources/mazeMap.txt");
	}

	char c;
	int i = 0;
	int j = 0;
	int characterIndex = 0;

	for (int i = 0; i < GameConstants::MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConstants::MAZE_WIDTH; j++)
		{
			tiles[i][j] = SPACE;
		}
	}

	while (!mapFile.eof())
	{
		mapFile.get(c);

		if (c == '#')
		{
			tiles[i][j] = WALL;
			j++;
		}
		else if (c == '*')
		{
			tiles[i][j] = FOOD;
			j++;
		}
		else if (c == '\n')
		{
			i++;
			j = 0;
		}
		else if(c == ' ')
		{
			tiles[i][j] = SPACE;
			j++;
		}

	}

	for (int i = 0; i < GameConstants::MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConstants::MAZE_WIDTH; j++)
		{
			if (tiles[i][j] == WALL)
			{
				walls[i*dim2 + j].setFillColor(sf::Color::Red);

				float debugX = j*GameConstants::TILE_SIZE;
				float debugY = i*GameConstants::TILE_SIZE;

				walls[i*dim2 + j].setPosition(debugX, debugY);
				walls[i*dim2 + j].setSize(sf::Vector2f(GameConstants::TILE_SIZE, GameConstants::TILE_SIZE));
			}
			else if(tiles[i][j] == FOOD)
			{
				food[i*dim2 + j].setPosition(sf::Vector2f(j*GameConstants::TILE_SIZE, i*GameConstants::TILE_SIZE));
			}
		}
	}
}

bool Maze::getFirstElement()
{
	return tiles[0][0];
}

void Maze::update()
{
	for (int i = 0; i < GameConstants::MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConstants::MAZE_WIDTH; j++)
		{
			if (tiles[i][j])
			{
				mazeSprite.setPosition(0, 0);
			}
		}
	}
}

bool Maze::isItWall(int i, int j)
{
	return tiles[i][j];
}
