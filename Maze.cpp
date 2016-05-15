#include <fstream>
#include <SFML\Graphics.hpp>
#include "Maze.h"

Maze::Maze()
{
	m_mazeSprite.setScale(GameConstants::SCALE, GameConstants::SCALE);
}

void Maze::setTexture(sf::Texture & spriteSheet)
{
	m_mazeSprite.setTexture(spriteSheet);
	m_mazeSprite.setTextureRect(sf::IntRect(GameConstants::MAZE_SPRITEX, GameConstants::MAZE_SPRITEY, GameConstants::MAZE_SPRITE_WIDTH, GameConstants::MAZE_SPRITE_HEIGHT));
}

void Maze::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_mazeSprite, states);
}

void Maze::buildMapMatrix(int dim1, int dim2, std::string mapName)
{
	std::ifstream mapFile;

	mapFile.open("resources/"+mapName);

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

	
}

void Maze::placeWalls(sf::RectangleShape *walls, int dim1, int dim2)
{
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
		}
	}
}

void Maze::placeFood(std::vector<Food> &food, int dim1, int dim2)
{
	for (int i = 0; i < GameConstants::MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConstants::MAZE_WIDTH; j++)
		{
			if (m_tiles[i][j] == FOOD)
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
