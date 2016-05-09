#include <fstream>
#include <SFML\Graphics.hpp>
#include "Maze.h"

Maze::Maze()
{
	m_spriteSheet.loadFromFile("spriteSheet2.png");
	m_mazeSprite.setTexture(m_spriteSheet);
	m_mazeSprite.setTextureRect(sf::IntRect(228, 0, 223, 247));
	m_mazeSprite.setScale(GameConstants::SCALE, GameConstants::SCALE);
}

void Maze::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_mazeSprite, states);
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
			m_tiles[i][j] = SPACE;
		}
	}

	while (!mapFile.eof())
	{
		mapFile.get(c);

		if (c == '#')
		{
			m_tiles[i][j] = WALL;
			j++;
		}
		else if (c == '*')
		{
			m_tiles[i][j] = FOOD;
			j++;
		}
		else if (c == '\n')
		{
			i++;
			j = 0;
		}
		else if(c == ' ')
		{
			m_tiles[i][j] = SPACE;
			j++;
		}

	}

	for (int i = 0; i < GameConstants::MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConstants::MAZE_WIDTH; j++)
		{
			if (m_tiles[i][j] == WALL)
			{
				walls[i*dim2 + j].setFillColor(sf::Color::Red);

				float debugX = j*GameConstants::TILE_SIZE;
				float debugY = i*GameConstants::TILE_SIZE;

				walls[i*dim2 + j].setPosition(debugX, debugY);
				walls[i*dim2 + j].setSize(sf::Vector2f(GameConstants::TILE_SIZE, GameConstants::TILE_SIZE));
			}
			else if(m_tiles[i][j] == FOOD)
			{
				food[i*dim2 + j].setPosition(sf::Vector2f(j*GameConstants::TILE_SIZE, i*GameConstants::TILE_SIZE));
			}
		}
	}
}

bool Maze::getFirstElement()
{
	return m_tiles[0][0];
}

void Maze::update()
{
	for (int i = 0; i < GameConstants::MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConstants::MAZE_WIDTH; j++)
		{
			if (m_tiles[i][j])
			{
				m_mazeSprite.setPosition(0, 0);
			}
		}
	}
}

bool Maze::isItWall(int i, int j)
{
	return m_tiles[i][j];
}
