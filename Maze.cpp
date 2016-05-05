#include "Maze.h"
#include <SFML\Graphics.hpp>
#include <fstream>
Maze::Maze(PacmanGame* game)
{
	m_game = game;

	tileSize = m_game->getTileSize();
	scale = m_game->getScale();
	mazeWidth = MAZE_WIDTH;
	mazeHeight = MAZE_HEIGHT;
	isDebugging = m_game->getIsDebugging;

	spriteSheet.loadFromFile("spriteSheet2.png");
	mazeSprite.setTexture(spriteSheet);
	mazeSprite.setTextureRect(sf::IntRect(228, 0, 223, 247));
	mazeSprite.setScale(scale, scale);

	//buildWallMatrix();
	
}

void Maze::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mazeSprite, states);

	if (isDebugging)
	{
		debugDraw(target);
	}
	
}

void Maze::debugDraw(sf::RenderTarget & target) const
{
	for (int i = 0; i < MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < MAZE_WIDTH; j++)
		{
			target.draw(m_walls[i][j]);
		}
	}
}

void Maze::buildWallMatrix(sf::RectangleShape *walls, int dim1, int dim2)
{
	std::ifstream mapFile;

	if (isDebugging)
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

			float debugX = characterIndex*tileSize;
			float debugY = i*tileSize;

			walls[i*dim2 + j].setPosition(debugX, debugY);
			walls[i*dim2 + j].setSize(sf::Vector2f(tileSize, tileSize));

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
	for (int i = 0; i < MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < MAZE_WIDTH; j++)
		{
			if (isWall[i][j])
			{
				mazeSprite.setPosition(0, 0);
			}
		}
	}
}

const int Maze::getScale()
{
	return scale;
}

const int Maze::getTileSize()
{
	return tileSize;
}

const bool Maze::getIsDebugging()
{
	return isDebugging;
}

const int Maze::getSheetTileSize()
{
	return tileSize;
}
