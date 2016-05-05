#include "Maze.h"
#include <SFML\Graphics.hpp>
#include <fstream>
Maze::Maze()
{
	spriteSheet.loadFromFile("spriteSheet2.png");
	mazeSprite.setTexture(spriteSheet);
	mazeSprite.setTextureRect(sf::IntRect(228, 0, 223, 247));
	mazeSprite.setScale(GameConstants::SCALE, GameConstants::SCALE);

	//buildWallMatrix();
	
}

void Maze::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mazeSprite, states);

	if (GameConstants::IS_DEBUGGING)
	{
		//debugDraw(target, states);
	}
	
}

void Maze::buildWallMatrix(sf::RectangleShape *walls, int dim1, int dim2)
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

	while (!mapFile.eof())
	{
		if ((i == 30) && (j == 4))
		{
			int tmp = 1;
		}
		mapFile.get(c);

		if (c == '#')
		{
			isWall[i][j] = true;

			walls[i*dim2 + j].setFillColor(sf::Color::Red);

			float debugX = characterIndex*GameConstants::TILE_SIZE;
			float debugY = i*GameConstants::TILE_SIZE;

			walls[i*dim2 + j].setPosition(debugX, debugY);
			walls[i*dim2 + j].setSize(sf::Vector2f(GameConstants::TILE_SIZE, GameConstants::TILE_SIZE));

			j++;
		}
		else if (c == ' ')
		{
			isWall[i][j] = false;
		}
		else if (c == '\n')
		{
			i++;
			characterIndex = -1;
			j = 0;
		}
		characterIndex++;

	}
}

bool Maze::getFirstElement()
{
	return isWall[0][0];
}




void Maze::update()
{
	for (int i = 0; i < GameConstants::MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConstants::MAZE_WIDTH; j++)
		{
			if (isWall[i][j])
			{
				mazeSprite.setPosition(0, 0);
			}
		}
	}
}
